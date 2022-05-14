const byte PinoChave = 2;  
volatile bool flag_chaveLigou = false;  
//Listagem 6: InterrupcaoPinoChaveFlagParaLoop (sem RTOS) 
void setup() {  
  Serial.begin(9600);  
    
  pinMode(PinoChave, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(PinoChave),  
  tratarInterrupcaoPinoChave, RISING);  
}  

void loop() {  
  if(flag_chaveLigou) 
  {  
    flag_chaveLigou = false;  
    Serial.print("Chave ligada!");  
  }  

  //Atividades diversas do sistema seriam executadas aqui, por exemplo!  
}  

void tratarInterrupcaoPinoChave() {  
  flag_chaveLigou = true;  
}
