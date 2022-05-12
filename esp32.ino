#include <WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64.h>

#define LED 2



//////////////////////
// WiFi Definitions //
//////////////////////
// WiFi configuration. Replace '***' with your data
const char* ssid     = "DRCL-17106";
const char* password = "DRCL1234!";
IPAddress server(192,168,79,8);      // Set the rosserial socket server IP address
const uint16_t serverPort = 11411;    // Set the rosserial socket server port




void forwardCallback(const std_msgs::Int16& msg) {
delay(500); 
digitalWrite(LED,HIGH); 
delay(500); 
digitalWrite(LED,LOW);
Serial.write(1);
Serial.print("forward");
}

void backCallback(const std_msgs::Int16& msg) {
delay(500); 
digitalWrite(LED,HIGH); 
delay(500); 
digitalWrite(LED,LOW);
delay(500); 
digitalWrite(LED,HIGH); 
delay(500); 
digitalWrite(LED,LOW);
Serial.write(2);
Serial.print("back");
}



ros::Subscriber<std_msgs::Int16> sub_f("/car/forward", &forwardCallback);
ros::Subscriber<std_msgs::Int16> sub_b("/car/back", &backCallback);




ros::NodeHandle nh;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();


  pinMode(LED,OUTPUT);  

  nh.subscribe(sub_f);
  nh.subscribe(sub_b);


}

void loop() {

  nh.spinOnce();
  delay(500);
}
