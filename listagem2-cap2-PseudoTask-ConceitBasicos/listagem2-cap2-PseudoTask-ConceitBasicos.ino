void trataInterrupcaoPinoEntrada(void) {  
  //Envia a informação do estado da chave  
  EnviaInformacaoParaATask(digitalRead(1)); 
} 
//Listagem 2 – Pseudocódigo de uma task em conjunto com uma interrupção 
void taskEnviaEstadoChave(void) { 
  
  //Variável local para ler a informação  
  char EstadoDaChave; 
  
  //loop principal da task 
  for(;;) { 
    //Espera chegar alguma informação para a task
    EstadoDaChave = RecebeInformacaoNaTask(); 
 
    if(EstadoDaChave == HIGH) { 
      Serial.println("Chave ligada!"); 
    } else { 
      Serial.println("Chave desligada!"); 
    }
  }
}

 
