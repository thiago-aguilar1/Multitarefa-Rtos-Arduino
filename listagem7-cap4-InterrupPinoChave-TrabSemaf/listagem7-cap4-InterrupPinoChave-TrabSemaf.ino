#include <Arduino_FreeRTOS.h>  
#include <semphr.h>  
//Listagem 7: InterrupcaoPinoChaveParaTask (usando RTOS) 
const byte PinoChave = 2;  
////////////// Flag eliminada !! ///////////////  
//volatile bool flag_chaveLigou = false;


//Semaforo binário para indicar evento da chave  
SemaphoreHandle_t xSemaforoBinarioChave;  

//Função da task para notificar o ligamento da chave  
void TaskChave( void *pvParametros );  
//Simula outras coisas que o programa precisa fazer constantemente  
void TaskOutrasAtividadesDoSistema( void *pvParametros );  


void setup() {
   
  BaseType_t xRet;  
  
  Serial.begin(9600);  
  
  pinMode(PinoChave, INPUT_PULLUP);  
    
  //Cria o semáforo binário  
  xSemaforoBinarioChave = xSemaphoreCreateBinary();  
     
  //Se tudo ok, cria a task  
  if(xSemaforoBinarioChave != NULL) {  
  
    xTaskCreate( TaskOutrasAtividadesDoSistema,  
     (const portCHAR *) "OutAtivSis", 128, NULL, 1, NULL);  
          
    xRet = xTaskCreate(  
     TaskChave  
     ,  (const portCHAR *) "TaskChave"  
     ,  128  // Stack size  
     ,  NULL  
     ,  2  // Priority  
     ,  NULL );   
       
    if(xRet == pdPASS)
    {  
      attachInterrupt(digitalPinToInterrupt(PinoChave),  
      tratarInterrupcaoPinoChave, RISING);  
    }  
    else  
    {  
      Serial.println("*** Erro ao criar task!");  
    }  
  }  
  else  
  {  
    Serial.println("*** Erro ao criar semaforo!");      
  }  
      
}  

void loop() {  
  //Monitoramento da flag saiu daqui  
}  

void tratarInterrupcaoPinoChave() {  
  //Variável para controle da mudança de task após sair da interrupção.   
  //Este esquema sempre deve ser feito para usar as função que terminal em FromISR  
  BaseType_t xHigherPriorityTaskWoken;    
  
  // Usa o semaforo para indicar evento da chave. Desbloquando a task que esperava por ele.  
  // Passa o endereço de xHigherPriorityTaskWoken para trata depois o escalonador antes de sair  
  // da interrpção.   
     
  xSemaphoreGiveFromISR( xSemaforoBinarioChave, &xHigherPriorityTaskWoken );    
    
  // Esta é a chamada que deve ser feita no final da ISR() para o freeRTOS mudar de tarefa,  
  //se for o caso  
  if( xHigherPriorityTaskWoken )  
  {  
    taskYIELD ();
  }    
}  

//Função da task para notificar o ligamento da chave  
void TaskChave( void *pvParametros ) {  
  //loop infinido da task  
  for( ;; )  
  {  
    //Espera o sinal de que a chave ligou   
    xSemaphoreTake( xSemaforoBinarioChave, portMAX_DELAY );  
    //Envia pela serial a informação  
    Serial.print("Chave ligada!");  
  }  
 
}  
   
//Simula outras coisas que o programa precisa fazer constantemente 
void TaskOutrasAtividadesDoSistema( void *pvParametros ) {  
   
  //Loop indinito  
  for(;;) {  
    //Atividades diversas do sistema seriam executadas aqui, por exemplo!  
  }  
}
