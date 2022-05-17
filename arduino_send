#include <PRIZM.h> 
  PRIZM prizm;
#include <SoftwareSerial.h>

#define PIN_TX 2
#define PIN_RX 2

SoftwareSerial Serial2(PIN_TX, PIN_RX);


void setup() {
  Serial2.begin(115200); 
  prizm.PrizmBegin(); 
  prizm.setMotorInvert(1,1);
}

void loop() 
{
  while(1)
  {
    prizm.resetEncoder(1);
    prizm.resetEncoder(2);
    int enco1 = prizm.readEncoderCount(1);
    int enco2 = prizm.readEncoderCount(2);
    Serial2.write(enco1);
    Serial2.write(enco2);
  }
}
