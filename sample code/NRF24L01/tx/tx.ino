/*
 * https://www.youtube.com/sanjulanipun
 * 
 * https://www.facebook.com/sanju.nipun
 * 
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 

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
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.b1     = digitalRead(2);
  data.b2     = digitalRead(3);
  data.b3     = digitalRead(4);
  data.b4     = digitalRead(5);
  delay(10);
  radio.write(&data, sizeof(MyData));
}
