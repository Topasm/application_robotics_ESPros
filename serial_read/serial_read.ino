
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5,11);
int data_in = 0;
void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  delay(100);


}
void loop() {
  // put your main code here, to run repeatedly:
  data_in = mySerial.read();
  Serial.printf("recieved date:%d", data_in);
delay(100);


}

