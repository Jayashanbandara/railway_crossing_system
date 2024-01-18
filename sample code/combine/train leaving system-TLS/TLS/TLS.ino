// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
int vib=digitalRead(2);
int train_come=0;
void setup()
{
   Serial.begin(9600);
   
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_tx_pin(3);
    vw_setup(3000);	 // Bits per sec
}


void t433MHZ()
{
     const char *msg = "Train_leave";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
   
    delay(200);
  }

void t433MHZ_arrieved()
{
     const char *msg = "Train_arrived";

    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(200);
  }
  
void vibrationx()
{ vib= digitalRead(2);
  }
void loop()
{ vibrationx();
  
  
   Serial.println(vib); 
    
  if (vib==1)

  {
    
    for (int i = 0; i <= 25; i++) {
    t433MHZ();
    delay(100);
    Serial.println("Train leaving"); 
  }
    /*train_come=0;*/
   
    }

   else{
    
    
    
    
    } 

}
