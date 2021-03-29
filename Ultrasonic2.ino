#include <Ultrasonic.h>
#include <ESP8266WiFi.h>  ////
#include <WiFiUdp.h>      ////
#include <SPI.h>
#include <ESP8266HTTPClient.h>

/*
  Comparação das saidas Digitais entre nodeMCU - Arduino
  NodeMCU – Arduino
  D0 = 16;
  D1 = 5;
  D2 = 4;
  D3 = 0;
  D4 = 2;   //IR
  D5 = 14;
  D6 = 12;
  D7 = 13;
  D8 = 15;
  D9 = 3;
  D10 = 1;
*/

// WiFi - Coloque aqui suas configurações de WI-FI
const char ssid[] = "casa";     // rede wifi sua casa
const char senha[] = "gato123"; // senha rede wifi

const int echoPin = 4;    //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)  D2 Esp8266
const int trigPin = 5;    //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)   D1 Esp8266
const int pinoLed = 13;   //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO       d7 esp8266

Ultrasonic ultrasonic(trigPin,echoPin); 
 
int distancia; 
String result; 

WiFiClient client;
HTTPClient http;

unsigned long lastConnectionTime = 0;        
boolean lastConnected = false;               

void setup(){
pinMode(echoPin, INPUT);     // Pino de entrada - recebe 
pinMode(trigPin, OUTPUT);    // Pino de saida - envia
pinMode(pinoLed, OUTPUT);    // Pino do saida - Led
Serial.begin(9600);          

 // Tenta conexão com Wi-fi
  WiFi.begin(ssid, senha);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(100);
    Serial.print(".");
  }
  Serial.print("\nWI-FI conectado com sucesso: ");
  Serial.println(ssid);
}


void loop(){

hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
Serial.print("Distancia "); 
Serial.print(result); 
Serial.println("cm"); 
if(distancia <= 30){             // Distancia 30cm
 digitalWrite(pinoLed,HIGH);     // Aciona o Led
 gravaweb();
}else{//SENÃO, FAZ
 // digitalWrite(pinoLed,LOW);   // Desliga o Led ou Não
}
}


// CALCULAR A DISTÂNCIA
void hcsr04(){
digitalWrite(trigPin, LOW);           
delayMicroseconds(2);                 
digitalWrite(trigPin, HIGH);          
delayMicroseconds(10);                
digitalWrite(trigPin, LOW);           
distancia = (ultrasonic.Ranging(CM)); 
result = String(distancia);
delay(500);                           
}
 

void gravaweb(){
  String  parametro;
  parametro = "texto=Distância: "+result+" CM";
  http.begin("http://xxx.com.br/xxx/mudaalarme.php");       // coloque aqui url hospedar os codigos fontes PHP       
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");        
  int httpCode = http.POST(parametro);    
  String payload = http.getString();    
  Serial.println(httpCode);   
  Serial.println(payload);    
  http.end();  
}
