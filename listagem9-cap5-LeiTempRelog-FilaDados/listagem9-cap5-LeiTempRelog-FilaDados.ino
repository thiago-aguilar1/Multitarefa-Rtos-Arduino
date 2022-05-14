#include <Arduino_FreeRTOS.h>
#include <queue.h> 
//Listagem 9: LeituraTemperaturaRelogioTexto 
//Tipo enumerado que indica que informação tem no item de fila  
typedef enum {tiLeituraTemperatura, tiHorario, tiTextoRecebido} TipoItem_t; 
  
//Tipo para os três tipos de dados (usa union) para interpretar a memÓria de cada jeito  
typedef struct { 
  TipoItem_t Tipo; 
  union { 
    float Temperatura;
    struct { 
      uint8_t Hora; 
      uint8_t Minutos; 
      uint8_t Segundos; 
    } Horario; 
    char Texto[13]; 
  } Dados; 
} ItemFila_t; 
     
//Identificador da fila unica  
QueueHandle_t xFila;  
     
void TaskLeituraTemp( void *pvParametros ); 
void TaskHoraAtual( void *pvParametros ); 
void TaskRecepcaoSerial( void *pvParametros ); 
void TaskEnvio( void *pvParametros ); 
    
int criarTasks(void) 
{ 
  if(xTaskCreate(TaskLeituraTemp, (const portCHAR *) "TaskLeituraTemp",  128, NULL, 2, NULL) == pdPASS) 
    Serial.println("Task TaskLeituraTemp criada com sucesso!"); 
  else 
    return 0;   
    
  if(xTaskCreate(TaskHoraAtual, (const portCHAR *) "TaskHoraAtual",  128, NULL, 2, NULL) == pdPASS) 
    //acho que não deveria ter essa linha vazia, mas é assim que está no livro.
    Serial.println("Task TaskHoraAtual criada com sucesso!"); 
  else 
    return 0;   
       
  if(xTaskCreate(TaskRecepcaoSerial, (const portCHAR *) "TaskRecepcaoSerial",  128, NULL, 2, NULL) == pdPASS) 
    Serial.println("Task TaskRecepcaoSerial criada com sucesso!"); 
  else 
    return 0;   
    
  if(xTaskCreate(TaskEnvio, (const portCHAR *) "TaskEnvio", 
   128, NULL, 2, NULL) == pdPASS) 
    Serial.println("Task TaskEnvio criada com sucesso!"); 
  else 
    return 0;   
       
  return 1; 
} 

void setup() { 
  BaseType_t xRet; 
 
  Serial.begin(9600); 
   
  // Cria a fila para as leituras de tmeperatura  
  xFila = xQueueCreate(10, sizeof( ItemFila_t ));  
  if(xFila)  
  { 
    Serial.println("Fila criado com sucesso!"); 
    if(!criarTasks()) 
    { 
      Serial.println("Ocorreu erro ao criar as tasks!"); 
    } 
  } 
  else 
  { 
    Serial.println("Ocorreu erro ao criar a fila!");
  } 
} 
  
void loop() { 
  //Monitoramento da flag saiu daqui  
} 
  
 
void TaskLeituraTemp( void *pvParametros ) 
{ 
  ItemFila_t Item; 
  Item.Tipo = tiLeituraTemperatura; 
  
  Serial.println("Inciando loop: TaskLeituraTemp");
  
  //loop da task 
  for( ;; )
  { 
    int sensorValue = analogRead(A0); 
    
    Item.Dados.Temperatura = (float(sensorValue)*5/(1023))/0.01; 
      
    xQueueSendToBack(xFila, &Item, portMAX_DELAY);  
       
    vTaskDelay(500 / portTICK_PERIOD_MS);
  } 
} 
   
void tratarRelogio(ItemFila_t *pItem) 
{ 
  pItem->Dados.Horario.Segundos++; 
  if(pItem->Dados.Horario.Segundos == 60) 
  { 
    pItem->Dados.Horario.Segundos = 0; 
    pItem->Dados.Horario.Minutos++; 
  
    if(pItem->Dados.Horario.Minutos == 60) 
    { 
      pItem->Dados.Horario.Minutos = 0; 
      pItem->Dados.Horario.Hora++; 
      if(pItem->Dados.Horario.Hora == 24) 
      { 
        pItem->Dados.Horario.Hora = 0; 
      } 
    } 
  } 
} 
   
  
void TaskHoraAtual( void *pvParametros ) 
{ 
  ItemFila_t Item; 
  Item.Tipo = tiHorario; 
  Item.Dados.Horario.Hora = 0; 
  Item.Dados.Horario.Minutos = 0; 
  Item.Dados.Horario.Segundos = 0; 
   
  Serial.println("Inciando loop: TaskRecepcaoSerial"); 
   
  //loop da task  
  for( ;; ) 
  { 
    tratarRelogio(&Item);
   
    xQueueSendToBack(xFila, &Item, portMAX_DELAY);  
   
    //espera um segundo 
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  } 
} 
   
void TaskRecepcaoSerial( void *pvParametros )
{ 
  ItemFila_t Item; 
  char carLido; 
   
  int tamanho = 0; 
   
  Item.Tipo = tiTextoRecebido; 
  Item.Dados.Texto[tamanho] = '\0'; 
  
  Serial.println("Inciando loop: TaskRecepcaoSerial"); 
  
  //loop da task  
  for( ;; ) 
  { 
    if(Serial.available()) 
    { 
      carLido = (char)Serial.read(); 
      if( carLido != '\n') 
      { 
        Item.Dados.Texto[tamanho++] = carLido; 
        Item.Dados.Texto[tamanho] = '\0' ; 
      } 
  
      if( (carLido == '\n') || (tamanho == (sizeof(Item.Dados.Texto)-1)) ) 
      { 
        xQueueSendToBack(xFila, &Item, portMAX_DELAY);  
        
        tamanho = 0;   
        Item.Dados.Texto[tamanho] = '\0';
      }       
    } 
  } 
} 
  
  
void TaskEnvio( void *pvParametros ) { 
  char EspelhoDisplay[2][17] = {"00:00:00 |      ",
                                "T: 000.0 |      "}; 
  ItemFila_t Item; 
  int l,i; 
  char *p; 
  
  
  Serial.println("Inciando loop: TaskEnvio"); 
  
  //loop da task  
  for( ;; ) 
  { 
    //Espera indefinidamente   
    xQueueReceive( xFila, &Item, portMAX_DELAY );  
  
    //de acordo com o tipo do item, atualiza o espelho do display e manda pela Serial  
    switch(Item.Tipo) 
    { 
      case tiLeituraTemperatura: 
        sprintf(&EspelhoDisplay[1][3], "%3.1f", Item.Dados.Temperatura); 
      break; 
  
      case tiHorario: 
        sprintf(&EspelhoDisplay[0][0], "%0.2d", 
          Item.Dados.Horario.Hora); 
        sprintf(&EspelhoDisplay[0][3], "%0.2d", 
          Item.Dados.Horario.Minutos); 
        sprintf(&EspelhoDisplay[0][6], "%0.2d", 
          Item.Dados.Horario.Segundos); 
      break; 
        
      case tiTextoRecebido  : 
        //acomoda parte do texto em 6 caracteres em cima e 6 na parte de baixo.  
        
        //limpa  
        
        for(l=0; l<2; l++)
        { 
          for(i=0, p = &EspelhoDisplay[l][10]; i<6; i++, p++) *p = ' '; 
          *p = '\0'; 
        } 
  
        //copia  
        for(l=0; l<2; l++) 
        { 
          p = &EspelhoDisplay[l][10]; 
          for(i=0; i<6 && Item.Dados.Texto[i]; i++) 
          { 
            *p = Item.Dados.Texto[i]; 
            p++; 
          } 
  
          *p = '\0'; 
        } 
        
      break;
    } 


    Serial.println("----------------"); 
    Serial.println(EspelhoDisplay[0]); 
    Serial.println(EspelhoDisplay[1]); 
  } 
}
