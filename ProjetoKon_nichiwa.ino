#include <IRremote.h>

#include <LiquidCrystal.h>

//Delay 

int tempo = 1000;

//Horario 

int horario = 0;

//Declaração Variáveis IR

int RECV_PIN = 9;

IRrecv irrecv(RECV_PIN);

decode_results results;

//Teclas do Controle

long int codTeclaOff = 16580863; //Tecla OFF
long int codTecla1 = 16582903; //Tecla 1
long int codTecla2 = 16615543; //Tecla 2
long int codTecla3 = 16599223; //Tecla 3 
long int codTecla4 = 16591063; //Tecla 4
long int codTecla5 = 16623703; //Tecla 5
long int codTecla6 = 16607383; //Tecla 6
long int codTecla9 = 16603303; //Botão 9 (Limpa Tela)

//Estado Led

int estadoLed1 = 0;
int estadoLed2 = 0;

//Estado Switch

int estadoSwitch1 = 0;

//Declararação de variáveis

  //Variáveis de Quantidade

  int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

  //LCD

  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

  //Switch

  int switch1 = 6;

  //LED´s

  int ledRed = 10;
  int ledGreen = 13;

  //Constante

  int cons = 1;

  //Constante para corrigir o resultado do 
    //Sensor Ultra-sónico

  int num = 00000.1;

  //Sensor Ultra-sónico

  int cm = 0; //centimetros

  //Sentenças
  
  //Sentença --> Bem vindo (Função)

  void digitalizacao(){
    
      lcd.clear();
    
      lcd.setCursor(3,0);
    
      lcd.print("Bem vindo!");
    
      lcd.setCursor(0,1);
    
      lcd.print("");   
      
      //lcd.print("いらっしゃいませ!");
  }

    //Sentença --> Confira os Descontos. (Função)

  void digitalizacao1(){
  
      lcd.clear();
      
      lcd.setCursor(0,0);
      
      lcd.print("Confira os");
      
      lcd.setCursor(0,1);
      
      lcd.print("Descontos.");
      
      //lcd.print("ディスカウントを確認して");
  }

  //Sentença --> Logo mais, vamos fechar. (Função)

  void digitalizacao2(){
  
    lcd.clear();
      
      lcd.setCursor(0,0);
      
      lcd.print("Logo mais,");
      
      lcd.setCursor(0,1);
      
      lcd.print("vamos fechar.");
      
      // lcd.print("もすぐ閉まってしまうよ");
   }

  //Sentença --> Estamos fechados. (Função)

  void digitalizacao3(){
  
      lcd.clear();
      
      lcd.setCursor(0,0);
      
      lcd.print("Estamos fechados");
      
      lcd.setCursor(0,1);
      
      lcd.print("");
      
      //lcd.print("閉まりました、休みです");
    
  
   }

  //Limpa Tela(Função)

  void digitalizacaoClear(){
 
      lcd.clear();
    
      lcd.setCursor(0,0);
    
      lcd.print("");
    
      lcd.setCursor(0,1);
    
      lcd.print("");    
   
    }
 

  //Função para Deslocamento da Sentença

  void deslocamento(){
 
      //Desloca o texto todo para a esquerda

        for(int i = 0;i<cons; i++){
      
          for (int posicao = 0; posicao < 15; posicao++)
          {
              lcd.scrollDisplayLeft();
          delay(100);         
          }

        //Desloca o texto todo para a direita

        for (int posicao; posicao < 15; posicao++)
        {
          lcd.scrollDisplayRight();
      delay(100);  
        }
  
        cons ++;

      }
    }


void setup()
{

  
  //Inciar comunicação serial
  
  Serial.begin(9600);
  
  //IR
  
  irrecv.enableIRIn();
  
  //LCD
 
  lcd.begin(16, 2);
  
  //Outros Elementos
  
  pinMode(switch1,INPUT);
  
  //OUTPUT
  
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT); 
}

void loop()
{
  
  //led Red --> Porta fechada
  //led Green --> Porta aberta

  digitalWrite(ledRed, HIGH); 
    
  
  //Relacionando o estado e o elemento Switch
  
  estadoSwitch1 = digitalRead(switch1);
 
  //Execução da função readDistance
  
  cm = 0.01723 * readDistance(7, 7);
  
  Serial.print(cm);
  Serial.println("cm");
  delay(100); //Espera por 100 millisecond(s)
  
  Serial.println(cm + num);
  delay(300);
  
  if (irrecv.decode(&results)) {
    
   //|| estadoSwitch == HIGH
   //Teste Tecla
  
    
    if((results.value == codTeclaOff) && (estadoLed1 == 0)){ 
    
    digitalWrite(ledRed, HIGH);
      estadoLed1 = 1;
     
   }
     
     if((results.value == codTeclaOff) && (estadoLed1 == 1)){
    
         digitalWrite(ledRed,LOW); 
         estadoLed1 = 0; 
   
   }
  
   
   //--------------------------------------//
    
    //Delay modificado pela interação com teclas
   
   //if(results.value == codTeclaVol+){
   
  
   // tempo = 10000;
   
   //}
     
   //if(results.value == codTeclaVol-){
   
   // tempo = 1500;
   
   //}
   
   //if(results.value == codTeclaEq){
     
   // tempo = 1000;
     
   //}
   
   //--------------------------------------//
   
   //Uso do Switch para limpar a Tela
    
   //Limpar LCD
   
   //if(estadoSwitch1 == HIGH){
     
     
   //  digitalizacaoClear();
     
     
   //}else{}

   //--------------------------------------//
  
   //Switch para mudar a variável horário
    
   if(estadoSwitch1 == HIGH){
     
     
     horario = 10;
     
   }  
   
    if(estadoSwitch1 == LOW){
      
     horario = 20;      
      
    }
    
    
    //Tecla 1 --> Sentença Bem Vindo! (digitalizacao)
    
    if((results.value == codTecla1)&& (d == 0)){
 
    digitalWrite(ledRed, LOW);
        
        digitalizacao();
     
        delay(1000);
      
        d = 1;
   
      digitalWrite(ledGreen, HIGH);  
      
        deslocamento();
    
        lcd.clear();
    
      digitalWrite(ledRed, HIGH);
    
    }else if((results.value == codTecla1) && (d == 1)){   
        
        deslocamento();
      
        d = 0;    
    }
      
     
   //Tecla 2 --> Confira os descontos. (digitalizacao1)
    
    
    if((results.value == codTecla2) && (c == 0)){
   
      digitalizacao1();
     
      c = 2;
   
      digitalWrite(ledGreen, HIGH);
    
      deslocamento(); 
     
   
   }else{  
     
     if((results.value == codTecla2) && (c == 2)){   
       
       digitalizacaoClear();  
       
       c = 0;
       
     }
   }
      
    //Tecla 3 --> Logo mais, vamos fechar.(digitalizacao2)
    
    if((results.value == codTecla3) && (b == 0)){
    
      digitalWrite(ledRed, LOW);
      
        digitalizacao2();
    
        b = 3;
      
      digitalWrite(ledGreen, HIGH);
      
        deslocamento();
      
        digitalWrite(ledRed, HIGH);
    
    }else{
      
       if((results.value == codTecla3) && (b == 3)){  
       
       digitalizacaoClear();  
       
       b = 0;  
         
       }   
   }
     
   
    //Tecla 4 --> Estamos fechados. (digitalizacao2)
    
    if((results.value == codTecla4) && (a == 0)){
     
      digitalWrite(ledRed, LOW);
      
        digitalizacao3();
       
        a = 4;
       
      digitalWrite(ledGreen, HIGH); 
      
        deslocamento();
    
        digitalWrite(ledRed, HIGH);
    
    }else{
       
       
       if((results.value == codTecla4) && (a == 4)){  
       
       digitalizacaoClear();
          
       a = 0;  
         
     
     }
   }
 
   if(results.value == codTecla9){
     
     
     digitalizacaoClear();
     
   }
 
 
 }

  
  //LCD Aproximação 0 a 24 cm
  
  if((cm >= 0)||(cm <= 24)){
    
    digitalWrite(ledRed, LOW);
    digitalizacao3(); 
    delay(1000);
    digitalWrite(ledGreen, HIGH);
    delay(2000); 
    digitalWrite(ledGreen, LOW);
    lcd.clear();
    digitalWrite(ledRed, HIGH);
    
  }
  
  //LCD Aproximação 25 a 49 cm
  
  if((cm >= 25)||(cm <= 49)){
    
    digitalWrite(ledRed, LOW);
    digitalizacao1(); 
    delay(1000);
    digitalWrite(ledGreen, HIGH);
    delay(2000);  
    digitalWrite(ledGreen, LOW);
    lcd.clear();
    digitalWrite(ledRed, HIGH);
    
  }
  
    //LCD Aproximação 50 a 75 cm
  
  if((cm >= 50)||(cm <= 75)){
  
    digitalWrite(ledRed, LOW);
    digitalizacao(); 
    delay(1000);
    digitalWrite(ledGreen, HIGH);
    delay(2000); 
    digitalWrite(ledGreen, LOW);
    lcd.clear();
    digitalWrite(ledRed, HIGH);
  
  }
  
  
}


  //Função de leitura da distância

long readDistance(int triggerPin, int echoPin){
  
  
  pinMode(triggerPin,OUTPUT); //Limpa a Leitura 
    digitalWrite(triggerPin, LOW);
    delay(200);
  
  //Setar o trigger pin para HIGH por 100 millisecond(s)
  
    digitalWrite(triggerPin, HIGH);
    delay(100);
    digitalWrite(triggerPin,LOW);
    pinMode(echoPin, INPUT);
  
  //Ler o Echo pin, e retorando o tempo do som
  
    return pulseIn(echoPin, HIGH);
  
}
