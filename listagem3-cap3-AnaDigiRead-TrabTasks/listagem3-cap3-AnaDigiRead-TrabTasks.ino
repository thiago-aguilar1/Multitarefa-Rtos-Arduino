#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).  
//Listagem 3: AnalogRead_DigitalRead (exemplo da biblioteca sem alguns comentários)
SemaphoreHandle_t xSerialSemaphore; 
 
// define two Tasks for DigitalRead & AnalogRead  
void TaskDigitalRead( void *pvParameters ); 
void TaskAnalogRead( void *pvParameters ); 
 
// the setup function runs once when[...]  
void setup() { 
 
  // initialize serial communication at 9600 bits per second:  
  Serial.begin(9600); 
  
  while (!Serial) { 
    ; 
  } 
 
  if ( xSerialSemaphore == NULL )
  { 
    xSerialSemaphore = xSemaphoreCreateMutex(); 
    if ( ( xSerialSemaphore ) != NULL ) 
      xSemaphoreGive( ( xSerialSemaphore ) ); 
  } 
 
  // Now set up two Tasks to run independently.  
  xTaskCreate( 
    TaskDigitalRead 
  ,  (const portCHAR *)"DigitalRead"  // A name just for humans  
  ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater  
  ,  NULL 
  ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.  
  ,  NULL ); 

  xTaskCreate( 
    TaskAnalogRead 
  ,  (const portCHAR *) "AnalogRead"
  ,  128  // Stack size  
  ,  NULL 
  ,  1  // Priority  
  ,  NULL ); 
  
  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.  
} 

void loop() 
{ 
  // Empty. Things are done in Tasks.  
} 
  
/*--------------------------------------------------*/  
/*---------------------- Tasks ---------------------*/  
/*--------------------------------------------------*/  
   
void TaskDigitalRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{ 
  // digital pin 2 has a pushbutton attached to it. Give it a name:  
  uint8_t pushButton = 2; 
   
  // make the pushbutton's pin an input:  
  pinMode(pushButton, INPUT); 
  
  for (;;) // A Task shall never return or exit.  
  { 
    // read the input pin:  
    int buttonState = digitalRead(pushButton); 
  
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ) 
    { 
      Serial.println(buttonState); 
    
      xSemaphoreGive( xSerialSemaphore ); 
    } 
    
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  } 
} 
     
void TaskAnalogRead( void *pvParameters __attribute__((unused)) )  // This is a Task.  
{ 
     
  for (;;) 
  { 
    // read the input on analog pin 0:  
    int sensorValue = analogRead(A0); 
    
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ) 
    { 
      Serial.println(sensorValue); 
      
      xSemaphoreGive( xSerialSemaphore ); 
    } 
       
    vTaskDelay(1);
  } 
}
