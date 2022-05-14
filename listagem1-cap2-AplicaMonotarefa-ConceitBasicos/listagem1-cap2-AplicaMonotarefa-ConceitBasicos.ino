void main(void) {  
  //Listagem 1 – Exemplo de um aplicativo monotarefa em C para microcontrolador  
  //Define o pino 13 como saída (LED) e 1 como entrada  
  pinMode(13, OUTPUT);  
  pinMode(1, INPUT);  
   
  //Inicia a serial com 9600 bps  
  Serial.begin(9600); 
 
  //loop principal  
  for(;;) { 
    digitalWrite(13, HIGH); 
    delay(1000); 
    digitalWrite(13, LOW); 
    delay(1000); 
   
    //Envia o estado da chave de entrada no pino 1  
    if(digitalRead(1) == HIGH) { 
      Serial.println("Chave ligada!"); 
    }else {
      Serial.println("Chave desligada!");      
    }
  }
}
