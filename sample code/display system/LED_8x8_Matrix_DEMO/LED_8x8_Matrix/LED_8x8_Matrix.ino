#include <LedControl.h>
int DIN = 10;
int CS =  9;
int CLK = 8 ;   

LedControl lc=LedControl(DIN,CLK,CS,0);

void setup(){
 lc.shutdown(0,false);       
 lc.setIntensity(0,1);      //Adjust the brightness maximum is 15
 lc.clearDisplay(0);    
}

void loop(){ 
  byte hart [8] = {0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18,0x00};
  byte sprite_Bro[8] = {B11111111,B10000001,B10100101,B10000001,B10100101,B10011001,B10000001,B11111111};

  
  printByte (hart); 
  delay (2000);

}

void printByte(byte character [])
{   int i = 0;
      for(i=0;i<8;i++){
        lc.setRow(0,i,character[i]);
        }
}
