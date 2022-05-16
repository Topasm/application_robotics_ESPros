#include <WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>

#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>

#define LED 2

int incoming_data = 0;


//////////////////////
// WiFi Definitions //
//////////////////////
// WiFi configuration. Replace '***' with your data
const char* ssid     = "DRCL-17106";
const char* password = "DRCL1234!";
IPAddress server(192,168,79,8);      // Set the rosserial socket server IP address
const uint16_t serverPort = 11411;    // Set the rosserial socket server port


std_msgs::Int32 encoder_msg;

ros::Publisher pub_encoder("encoder", &encoder_msg);
// ros::Publisher chatter("chatter", &str_msg);
ros::NodeHandle nh;

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


unsigned long publishing_timer;

void wifisetup()
{
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
  nh.initNode();
  nh.advertise(pub_encoder);


}

void setup() {
  Serial.begin(115200);
  Serial.println();
  wifisetup();
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();


  pinMode(LED,OUTPUT);  

  nh.subscribe(sub_f);
  nh.subscribe(sub_b);


}

void loop() {

  nh.spinOnce();
  delay(500);

  if(millis() >publishing_timer)
  {
    incoming_data =  Serial.read();
    Serial.print("recieved date:");
    Serial.println(incoming_data, DEC);
    encoder_msg.data = incoming_data;
    pub_encoder.publish(&encoder_msg);

    publishing_timer = millis()+1000;


  }
  

    
}