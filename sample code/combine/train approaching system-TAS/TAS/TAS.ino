#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <VirtualWire.h>
RF24 radio(7,8);
int vibration=2;
const byte address[6] = "00001";
String Word="";

int vib=digitalRead(2);
void setup() {
  Serial.begin(9600);  // Debugging only
  Serial.println("setup");
 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.stopListening();
  
  //t433mhz
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(3);
  vw_setup(4000);   // Bits per sec

  vw_rx_start();       // Start the receiver PLL running  
  


}

void r433MHZ()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

        digitalWrite(13, true); // Flash a light to show received good message
  // Message with a good checksum received, dump it.
  Serial.print("Got: ");

  for (i = 0; i < buflen; i++)
  {    
      Word=Word+char(buf[i]);
      //Serial.print(char(buf[i]));
      //Serial.print("");
  }
  Serial.println("");
        digitalWrite(13, false);
    }
  
  
  }

void nrf()
{ const char text[] = "Trainaproach";
  radio.write(&text, sizeof(text));
  delay(2000);
  
  }
void vibrationx()
{ vib= digitalRead(2);
  }

void loop() {
   vibrationx();
   r433MHZ();
   //Serial.println(Word);
   //Serial.print(digitalRead(2));
   //delay(1000);
   if ((vib)&&(Word=="train_here"))
   {Serial.print("ok");
    nrf();
    }
   Word="";
}
