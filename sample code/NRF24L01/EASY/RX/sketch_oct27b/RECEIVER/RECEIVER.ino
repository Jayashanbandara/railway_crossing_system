#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int x=0;
RF24 radio(7,8);

const int buzzer = 2;
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.startListening();
}

void loop() {
  char text[32] = "";
  
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    Serial.print(String(text)); 
    Serial.print("\t"); 
    Serial.println(x);
    x+=1;
     
  }
 
}
