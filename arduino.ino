#include <PRIZM.h> 
  PRIZM prizm;
#include <SoftwareSerial.h>

#define PIN_TX 1
#define PIN_RX 2

SoftwareSerial Serial2(PIN_TX, PIN_RX);


void setup() {
  Serial2.begin(115200); 
  prizm.PrizmBegin(); 
  prizm.setMotorInvert(1,1);
  int buff = 0;
}

void loop() {
  if (Serial2.available())
  { 
    int buff = Serial2.read();
    if(buff=1)
    {
      prizm.setMotorPowers(35,35);      
      delay(500);
      int buff = 0;
    }
    else if(buff=1)
    {
      prizm.setMotorPowers(35,35);      
      delay(500);
      int buff = 0;
    }
    else
    {
      prizm.setMotorPowers(125,125);      
      delay(500);
      int buff = 0;
    }
  }
}
