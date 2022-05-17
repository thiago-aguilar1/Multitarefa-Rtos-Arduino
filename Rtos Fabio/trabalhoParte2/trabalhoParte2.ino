//Listagem 4: AnalogRead_DigitalReadModificadoVariosLeitores

#include <Arduino_FreeRTOS.h> 
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
 
SemaphoreHandle_t xBuzzerSemaphore;

void TaskMarioBros( void *pvParameters );

void TaskDarthVader( void *pvParameters );

void TaskIronMaider( void *pvParameters );



// --- Funções Auxiliares ---        apenas as assinaturas  / protótipos das funções usadas pelo Darth Vader 
void march(char oitava);
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds);








void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  
  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xBuzzerSemaphore == NULL )  // Check to confirm that the     Semaphore has not already been created.
  {
    xBuzzerSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the 
    if ( ( xBuzzerSemaphore ) != NULL )
      xSemaphoreGive( ( xBuzzerSemaphore ) );  // Make the       available for use, by "Giving" the Semaphore.
  }


  
  

  xTaskCreate(
  TaskMarioBros
  ,  (const portCHAR *)"ParDeLeds"  // A name just for humans
  ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
  ,  NULL
  ,  1  
  ,  NULL );
  
  xTaskCreate(
  TaskMarioBros
  ,  (const portCHAR *)"SuperMarioBros"  // A name just for humans
  ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
  ,  NULL
  ,  1  
  ,  NULL );

  xTaskCreate(
  TaskDarthVader
  ,  (const portCHAR *)"MarchaImperialStarWars"  // A name just for humans
  ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
  ,  NULL
  ,  1 
  ,  NULL );

  xTaskCreate(
  TaskIronMaider
  ,  (const portCHAR *)"FearOfTheDark"  // A name just for humans
  ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
  ,  NULL
  ,  1 
  ,  NULL );

 


 
  
  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}



void loop()
{
  // Empty. Things are done in Tasks.
}



void SerialDebugComSemaforo(const char *pszTexto)
{
  if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
  {
    Serial.print(pszTexto);
    xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
  }
}



/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/





void TaskDigitalRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
  DigitalReadSerial
  Reads a digital input on pin 2, prints the result to the serial monitor
  This example code is in the public domain.
  */
  
  // digital pin 2 has a pushbutton attached to it. Give it a name:
  uint8_t pushButton = 2;
  
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  
  
  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    int buttonState = digitalRead(pushButton);
    
    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xBuzzerSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      Serial.println(buttonState);   
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
  
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
  
}







void TaskMarioBros( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  
/*************************************************
* Public Constants
*************************************************/   

  #define NOTE_B0 31
  #define NOTE_C1 33
  #define NOTE_CS1 35
  #define NOTE_D1 37
  #define NOTE_DS1 39
  #define NOTE_E1 41
  #define NOTE_F1 44
  #define NOTE_FS1 46
  #define NOTE_G1 49
  #define NOTE_GS1 52
  #define NOTE_A1 55
  #define NOTE_AS1 58
  #define NOTE_B1 62
  #define NOTE_C2 65
  #define NOTE_CS2 69
  #define NOTE_D2 73
  #define NOTE_DS2 78
  #define NOTE_E2 82
  #define NOTE_F2 87
  #define NOTE_FS2 93
  #define NOTE_G2 98
  #define NOTE_GS2 104
  #define NOTE_A2 110
  #define NOTE_AS2 117
  #define NOTE_B2 123
  #define NOTE_C3 131
  #define NOTE_CS3 139
  #define NOTE_D3 147
  #define NOTE_DS3 156
  #define NOTE_E3 165
  #define NOTE_F3 175
  #define NOTE_FS3 185
  #define NOTE_G3 196
  #define NOTE_GS3 208
  #define NOTE_A3 220
  #define NOTE_AS3 233
  #define NOTE_B3 247
  #define NOTE_C4 262
  #define NOTE_CS4 277
  #define NOTE_D4 294
  #define NOTE_DS4 311
  #define NOTE_E4 330
  #define NOTE_F4 349
  #define NOTE_FS4 370
  #define NOTE_G4 392
  #define NOTE_GS4 415
  #define NOTE_A4 440
  #define NOTE_AS4 466
  #define NOTE_B4 494
  #define NOTE_C5 523
  #define NOTE_CS5 554
  #define NOTE_D5 587
  #define NOTE_DS5 622
  #define NOTE_E5 659
  #define NOTE_F5 698
  #define NOTE_FS5 740
  #define NOTE_G5 784
  #define NOTE_GS5 831
  #define NOTE_A5 880
  #define NOTE_AS5 932
  #define NOTE_B5 988
  #define NOTE_C6 1047
  #define NOTE_CS6 1109
  #define NOTE_D6 1175
  #define NOTE_DS6 1245
  #define NOTE_E6 1319
  #define NOTE_F6 1397
  #define NOTE_FS6 1480
  #define NOTE_G6 1568
  #define NOTE_GS6 1661
  #define NOTE_A6 1760
  #define NOTE_AS6 1865
  #define NOTE_B6 1976
  #define NOTE_C7 2093
  #define NOTE_CS7 2217
  #define NOTE_D7 2349
  #define NOTE_DS7 2489
  #define NOTE_E7 2637
  #define NOTE_F7 2794
  #define NOTE_FS7 2960
  #define NOTE_G7 3136
  #define NOTE_GS7 3322
  #define NOTE_A7 3520
  #define NOTE_AS7 3729
  #define NOTE_B7 3951
  #define NOTE_C8 4186  
  #define NOTE_CS8 4435
  #define NOTE_D8 4699
  #define NOTE_DS8 4978

  #define melodyPin 3      // Serve para todas, não só para o código do Mário World ***********

  byte ledPin = 13;       // Para a do Vader (Marcha Imperial) também serve *****

  int song = 0;

  //Mario main theme melody
  int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0, 0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
  };
  //Mario main them tempo
  int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  };
  //Underworld melody
  int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
  };
  //Underwolrd tempo
  int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
  };




   
  for (;;)
  {
    
    int sensorValue = analogRead(pxParams->SensorID);
    
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
        
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
     
    vTaskDelay(pxParams->TempoDelayTicks);  // one tick delay (15ms) in between reads for stability
  }
   
}








void TaskDarthVader( void *pvParameters __attribute__((unused)) )  // This is a Task.
{


  int speakerPin = 3;

  #define c 261
  #define d 294
  #define e 329
  #define f 349
  #define g 391
  #define gS 415
  #define a 440
  #define aS 455
  #define b 466
  #define cH 523
  #define cSH 554
  #define dH 587
  #define dSH 622
  #define eH 659
  #define fH 698
  #define fSH 740
  #define gH 784
  #define gSH 830
  #define aH 880
  //frequencies for the tones we're going to use
  //used http://home.mit.bme.hu/~bako/tonecalc/tonecalc.htm to get these



  
  
 
  for (;;)
  {
    
    int sensorValue = analogRead(pxParams->SensorID);
    
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
        
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
     
    vTaskDelay(pxParams->TempoDelayTicks);  // one tick delay (15ms) in between reads for stability
  }
   
}










void TaskIronMaider( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

    
/*************************************************
* Public Constants
*************************************************/   

  #define NOTE_B0 31
  #define NOTE_C1 33
  #define NOTE_CS1 35
  #define NOTE_D1 37
  #define NOTE_DS1 39
  #define NOTE_E1 41
  #define NOTE_F1 44
  #define NOTE_FS1 46
  #define NOTE_G1 49
  #define NOTE_GS1 52
  #define NOTE_A1 55
  #define NOTE_AS1 58
  #define NOTE_B1 62
  #define NOTE_C2 65
  #define NOTE_CS2 69
  #define NOTE_D2 73
  #define NOTE_DS2 78
  #define NOTE_E2 82
  #define NOTE_F2 87
  #define NOTE_FS2 93
  #define NOTE_G2 98
  #define NOTE_GS2 104
  #define NOTE_A2 110
  #define NOTE_AS2 117
  #define NOTE_B2 123
  #define NOTE_C3 131
  #define NOTE_CS3 139
  #define NOTE_D3 147
  #define NOTE_DS3 156
  #define NOTE_E3 165
  #define NOTE_F3 175
  #define NOTE_FS3 185
  #define NOTE_G3 196
  #define NOTE_GS3 208
  #define NOTE_A3 220
  #define NOTE_AS3 233
  #define NOTE_B3 247
  #define NOTE_C4 262
  #define NOTE_CS4 277
  #define NOTE_D4 294
  #define NOTE_DS4 311
  #define NOTE_E4 330
  #define NOTE_F4 349
  #define NOTE_FS4 370
  #define NOTE_G4 392
  #define NOTE_GS4 415
  #define NOTE_A4 440
  #define NOTE_AS4 466
  #define NOTE_B4 494
  #define NOTE_C5 523
  #define NOTE_CS5 554
  #define NOTE_D5 587
  #define NOTE_DS5 622
  #define NOTE_E5 659
  #define NOTE_F5 698
  #define NOTE_FS5 740
  #define NOTE_G5 784
  #define NOTE_GS5 831
  #define NOTE_A5 880
  #define NOTE_AS5 932
  #define NOTE_B5 988
  #define NOTE_C6 1047
  #define NOTE_CS6 1109
  #define NOTE_D6 1175
  #define NOTE_DS6 1245
  #define NOTE_E6 1319
  #define NOTE_F6 1397
  #define NOTE_FS6 1480
  #define NOTE_G6 1568
  #define NOTE_GS6 1661
  #define NOTE_A6 1760
  #define NOTE_AS6 1865
  #define NOTE_B6 1976
  #define NOTE_C7 2093
  #define NOTE_CS7 2217
  #define NOTE_D7 2349
  #define NOTE_DS7 2489
  #define NOTE_E7 2637
  #define NOTE_F7 2794
  #define NOTE_FS7 2960
  #define NOTE_G7 3136
  #define NOTE_GS7 3322
  #define NOTE_A7 3520
  #define NOTE_AS7 3729
  #define NOTE_B7 3951
  #define NOTE_C8 4186  
  #define NOTE_CS8 4435
  #define NOTE_D8 4699
  #define NOTE_DS8 4978

  #define melodyPin 3      // Serve para todas, não só para o código do Mário World ***********

  int melodia[] =    {NOTE_D6,NOTE_A5,NOTE_A5,NOTE_D6,NOTE_D6,NOTE_E6,NOTE_E6,NOTE_F6,NOTE_F6,NOTE_E6,NOTE_E6,NOTE_D6,NOTE_D6,NOTE_E6,NOTE_E6,NOTE_C6,NOTE_G5,NOTE_G5,NOTE_C6,NOTE_C6,NOTE_D6,NOTE_D6,NOTE_E6,NOTE_E6,NOTE_D6,NOTE_D6,NOTE_C6,NOTE_C6,NOTE_E6,NOTE_E6,NOTE_C6,NOTE_C6,NOTE_D6,NOTE_A5,NOTE_A5,NOTE_D6,NOTE_D6,NOTE_E6,NOTE_E6,NOTE_F6,NOTE_F6,NOTE_E6,NOTE_E6,NOTE_D6,NOTE_D6,NOTE_E6,NOTE_E6,NOTE_C6,NOTE_G5,NOTE_G5,NOTE_C6,NOTE_C6,NOTE_D6,NOTE_D6,NOTE_E6,NOTE_E6,NOTE_D6,NOTE_D6,NOTE_C6,NOTE_C6,NOTE_E6,NOTE_E6,NOTE_C6,NOTE_C6,NOTE_A5,NOTE_A5,NOTE_E5,NOTE_E5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_B5,NOTE_C6,NOTE_C6,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_A5,NOTE_D5,NOTE_D5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_A5,NOTE_G5,NOTE_G5,NOTE_B5,NOTE_G5,NOTE_A5,NOTE_A5,NOTE_E5,NOTE_E5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_B5,NOTE_C6,NOTE_C6,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_A5,NOTE_B5,NOTE_B5,NOTE_F5,NOTE_F5,NOTE_D5,NOTE_D5,NOTE_F5,NOTE_F5,NOTE_A5,NOTE_A5,NOTE_G5,NOTE_G5,NOTE_F5,NOTE_F5,NOTE_G5,NOTE_F5}   ;
  int tempoNot[] = {   2,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      2,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,   2,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      2,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,   4 ,     4,      4,       4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,     4};// Duração d Not: Colcheia:8; Semínima: 4; Mínima:2; Semibreve:1

  const int compso = 550; // Altera o compso da música 

  
  
  for (;;)
  {
    
    int sensorValue = analogRead(pxParams->SensorID);
    
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
        
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
     
    vTaskDelay(pxParams->TempoDelayTicks);  // one tick delay (15ms) in between reads for stability
  }
   
}
















//*************************************************************************************************************************************
//************************************    A funções que serão chamadas pelas tasks  ***************************************************
//*************************************************************************************************************************************






















//  *************************       Funções do Darth Vader ( Marcha Imperial, de Star Wars)      **************************


void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{
    digitalWrite(ledPin, HIGH);
    //use led to visualize the notes being played
 
    int x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)    {
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }
 
    digitalWrite(ledPin, LOW);
    //set led back to low
 
    delay(20);
    //a little delay to make all notes sound separate
}
 
void march(char oitava)
{
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
 
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*f, 350);
    beep(speakerPin, oitava*cH, 150);
 
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*f, 350);
    beep(speakerPin, oitava*cH, 150);
    beep(speakerPin, oitava*a, 1000);
    //first bit
 
    beep(speakerPin, oitava*eH, 500);
    beep(speakerPin, oitava*eH, 500);
    beep(speakerPin, oitava*eH, 500);
    beep(speakerPin, oitava*fH, 350);
    beep(speakerPin, oitava*cH, 150);
 
    beep(speakerPin, oitava*gS, 500);
    beep(speakerPin, oitava*f, 350);
    beep(speakerPin, oitava*cH, 150);
    beep(speakerPin, oitava*a, 1000);
    //second bit...
 
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*a, 350);
    beep(speakerPin, oitava*a, 150);
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*gSH, 250);
    beep(speakerPin, oitava*gH, 250);
 
    beep(speakerPin, oitava*fSH, 125);
    beep(speakerPin, oitava*fH, 125);
    beep(speakerPin, oitava*fSH, 250);
    delay(250);
    beep(speakerPin, oitava*aS, 250);
    beep(speakerPin, oitava*dSH, 500);
    beep(speakerPin, oitava*dH, 250);
    beep(speakerPin, oitava*cSH, 250);
    //start of the interesting bit
 
    beep(speakerPin, oitava*cH, 125);
    beep(speakerPin, oitava*b, 125);
    beep(speakerPin, oitava*cH, 250);
    delay(250);
    beep(speakerPin, oitava*f, 125);
    beep(speakerPin, oitava*gS, 500);
    beep(speakerPin, oitava*f, 375);
    beep(speakerPin, oitava*a, 125);
 
    beep(speakerPin, oitava*cH, 500);
    beep(speakerPin, oitava*a, 375);
    beep(speakerPin, oitava*cH, 125);
    beep(speakerPin, oitava*eH, 1000);
    //more interesting stuff (this doesn't quite get it right somehow)
 
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*a, 350);
    beep(speakerPin, oitava*a, 150);
    beep(speakerPin, oitava*aH, 500);
    beep(speakerPin, oitava*gSH, 250);
    beep(speakerPin, oitava*gH, 250);
 
    beep(speakerPin, oitava*fSH, 125);
    beep(speakerPin, oitava*fH, 125);
    beep(speakerPin, oitava*fSH, 250);
    delay(250);
    beep(speakerPin, oitava*aS, 250);
    beep(speakerPin, oitava*dSH, 500);
    beep(speakerPin, oitava*dH, 250);
    beep(speakerPin, oitava*cSH, 250);
    //repeat... repeat
 
    beep(speakerPin, oitava*cH, 125);
    beep(speakerPin, oitava*b, 125);
    beep(speakerPin, oitava*cH, 250);
    delay(250);
    beep(speakerPin, oitava*f, 250);
    beep(speakerPin, oitava*gS, 500);
    beep(speakerPin, oitava*f, 375);
    beep(speakerPin, oitava*cH, 125);
 
    beep(speakerPin, oitava*a, 500);
    beep(speakerPin, oitava*f, 375);
    beep(speakerPin, oitava*c, 125);
    beep(speakerPin, oitava*a, 1000);
    //and we're done \ó/
}

















//   *********************************  função do  Iron Maider ( música Fear of the Dark )   *********************************


void ironMaider() {
  for (int Nota = 0; Nota < 128; Nota++) {//o número 80 indica quant not tem a nossa matriz.
    int tempo = compso/tempoNot[Nota]; //Tempo = compso dividido pela indicação da matriz tempoNot.
    tone(melodyPin, melodia[Nota],tempo); //Toca a nota indicada pela matriz melodia durante o tempo.
    // Para distinguir  not adicionamos um tempo entre elas (tempo da nota + 20%).
    delay(tempo*1.2);
  }
}
