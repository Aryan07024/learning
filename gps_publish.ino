#include <SoftwareSerial.h> 
#include<ros.h>
#include <TinyGPS++.h>
#include<geometry_msgs/Point.h>
#define RXPin 18
#define TXPin 19
SoftwareSerial ss(RXPin, TXPin);

TinyGPSPlus gps;


unsigned long lastUpdateTime = 0;
ros::NodeHandle nh;
geometry_msgs::Point gps_msg;
ros::Publisher gps_data("gps_data",&gps_msg);


void setup() {

   Serial.begin(115200);
  ss.begin(9600);
 nh.initNode();
  nh.advertise(gps_data);
 // put your setup code here, to run once:

}

void loop() {

   while (ss.available() > 0)
  //  getGPS();
    gps.encode(ss.read());

    if(gps.satellites.value()>3)
    {

  if (millis() - lastUpdateTime >= 500)
  {
    lastUpdateTime = millis();
    if(gps.location.isValid())
    {
      gps_msg.x=gps.location.lat();
     gps_msg.y=gps.location.lng();}
    if(gps.altitude.isValid())
    gps_msg.z=gps.altitude.meters();
  
  
  }}
  
gps_data.publish(&gps_msg);
nh.spinOnce();
  // put your main code here, to run repeatedly:

}
