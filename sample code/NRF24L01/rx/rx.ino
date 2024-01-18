/*
   https://www.youtube.com/sanjulanipun

   https://www.facebook.com/sanju.nipun

*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeIn = 0xE8E8F0F0E1LL;

RF24 radio(9, 10);


struct MyData {
  byte b1;
  byte b2;
  byte b3;
  byte b4;
 
};

MyData data;

void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);

  radio.openReadingPipe(1, pipeIn);
  radio.startListening();

}



void rxData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));

    if (data.b1 = 1) {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
    if (data.b2 = 1) {
      digitalWrite(3, HIGH);
    } else {
      digitalWrite(3, LOW);
    }
    if (data.b3 = 1) {
      digitalWrite(4, HIGH);
    } else {
      digitalWrite(4, LOW);
    }
  
  }
}

void loop()
{
  rxData();

  Serial.print("Button 1 : ");
  Serial.print(data.b1);
  Serial.print("    ");

  Serial.print("Button 2 ");
  Serial.print(data.b2);
  Serial.print("    ");

  Serial.print("Button 3 ");
  Serial.print(data.b3);
  Serial.print("    ");

  Serial.print("Button 4 ");
  Serial.print(data.b4);
  Serial.print("\n");

}


