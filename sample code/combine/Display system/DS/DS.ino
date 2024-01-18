#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>
#include <VirtualWire.h>

RF24 radio(9,10);
String Word="";
const int buzzer = 2;
const byte address[6] = "00001";
String TLS="";
boolean trx=0;

const int rs = 7, en = 6, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  lcd.begin(16, 2);// Print a message to the LCD.
  lcd.print("! SYSTEM START !");
  delay(1000);
  lcd.clear();
  digitalWrite(A0,0);
 digitalWrite(A1,255);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.startListening();


  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(8);
  vw_setup(3000);   // Bits per sec

  vw_rx_start();       // Start the receiver PLL running  
}

void display_system()
{

  lcd.print("Train arriving");
  delay(1000);
  lcd.clear();
  delay(500);
  }
void nrf()
{
    char text[32] = "";
  
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    String transData = String(text);
    Word=String(text);
    Serial.println(String(text)); 
    Serial.print("\t"); 
    //Serial.println(x);
    //x+=1;
     
  }
  
  
  }

void r433MHZ()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

        // Flash a light to show received good message
  // Message with a good checksum received, dump it.
  //Serial.print("Got: ");

  for (i = 0; i < buflen; i++)
  {    
      TLS=TLS+char(buf[i]);
      //Serial.print(char(buf[i]));
      //Serial.print("");
  }
  /*Serial.println(TLS);
        digitalWrite(13, false);*/
    }
  
  }


void loop() {
//Serial.println(Word);
Serial.print(TLS);
nrf();
r433MHZ();
if(Word=="Trainaproach")

{display_system();
  //trx=1;
 
}

if ((trx==1)&&(TLS=="Train_leave"))
{
  for (int i = 0; i <= 5; i++) {
    lcd.print("Train leaving");
    delay(1000);
    Serial.print("Train leaving");
    lcd.clear();
    delay(500);
  
  } 
  trx=0;
  TLS="";
  }


/*else if(trx==1){
  
  display_system();
  
  }*/
else
{
  digitalWrite(0,LOW); }
  
 Word="";
 
}
