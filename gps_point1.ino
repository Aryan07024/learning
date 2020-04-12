#include <SoftwareSerial.h> 
#include <TinyGPS++.h>
#define RXPin 18
#define TXPin 19
#define speedLow 30              //to be check  
#define speedHigh 50             //to be check


Double lat[5] = {};             //lenght and gpspoint 
int noofpoint =5;                                 //to be enterred
Double lon[5] = {};              
int start a=0;
SoftwareSerial ss(RXPin, TXPin);

TinyGPSPlus gps;
unsigned long lastUpdateTime = 0;
int l1a=31 ;
int l2a =32;
int l3a =33;
int r1a = 34;
int r2a = 35;
int r3a = 36;
int l1b = 37 ;
int l2b = 38;
int l3b = 39;
int r1b = 40;
int r2b = 41;
int r3b = 42;
int speed1l = 2;
int speed2l = 3;
int speed3l = 4;
int speed1r = 5;
int speed2r = 6;
int speed3r = 7;


void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  pinMode(l1a,OUTPUT);
pinMode(l2a,OUTPUT);
pinMode(l3a,OUTPUT);
pinMode(r1a,OUTPUT);
pinMode(r2a,OUTPUT);
pinMode(r3a,OUTPUT);
pinMode(l1b,OUTPUT);
pinMode(l2b,OUTPUT);
pinMode(l3b,OUTPUT);
pinMode(r1b,OUTPUT);
pinMode(r2b,OUTPUT);
pinMode(r3b,OUTPUT);
pinMode(speed1l,OUTPUT);
pinMode(speed2l,OUTPUT);
pinMode(speed3l,OUTPUT);
pinMode(speed1r,OUTPUT);
pinMode(speed2r,OUTPUT);
pinMode(speed3r,OUTPUT);
}

void forward(int a)
{
 digitalWrite(r1a,1);
  digitalWrite(r1b,0);
  digitalWrite(r2a,1);
  digitalWrite(r2b,0);
  digitalWrite(r2a,1);
  digitalWrite(r2b,0);
  digitalWrite(l1a,1);
  digitalWrite(l1b,0);
  digitalWrite(l2a,1);
  digitalWrite(l2b,0);
  digitalWrite(l2a,1);
  digitalWrite(l2b,0); 
  analogWrite(speed1l,a);
  analogWrite(speed2l,a);
  analogWrite(speed3l,a);
  analogWrite(speed1r,a);
  analogWrite(speed1r,a);
  analogWrite(speed1r,a);
}
void right(int a)
{
  analogWrite(speed1l,a);
  analogWrite(speed2l,a);
  analogWrite(speed3l,a);
  analogWrite(speed1r,a);
  analogWrite(speed1r,a);
  analogWrite(speed1r,a);
  digitalWrite(r1a,0);
  digitalWrite(r1b,1);
  digitalWrite(r2a,0);
  digitalWrite(r2b,1);
  digitalWrite(r2a,0);
  digitalWrite(r2b,1);
  digitalWrite(l1a,1);
  digitalWrite(l1b,0);
  digitalWrite(l2a,1);
  digitalWrite(l2b,0);
  digitalWrite(l2a,1);
  digitalWrite(l2b,0);
  
}

void left (int a)
{
  analogWrite(speed1l,a);
  analogWrite(speed2l,a);
  analogWrite(speed3l,a);
  analogWrite(speed1r,a);
  analogWrite(speed1r,a);
  analogWrite(speed1r,a);
  digitalWrite(r1a,1);
  digitalWrite(r1b,0);
  digitalWrite(r2a,1);
  digitalWrite(r2b,0);
  digitalWrite(r2a,1);
  digitalWrite(r2b,0);
  digitalWrite(l1a,0);
  digitalWrite(l1b,1);
  digitalWrite(l2a,0);
  digitalWrite(l2b,1);
  digitalWrite(l2a,0);
  digitalWrite(l2b,1);
}
void stop ()
{
  analogWrite(speed1l,0);
  analogWrite(speed2l,0);
  analogWrite(speed3l,0);
  analogWrite(speed1r,0);
  analogWrite(speed1r,0);
  analogWrite(speed1r,0);
}

void loop()
{
  while(start<noofpoint)
  {
  while (ss.available() > 0)
    getGPS();
    gps.encode(ss.read());

  if (millis() - lastUpdateTime >= 500)
  {
    lastUpdateTime = millis();
    Serial.println();
    double distanceToDestination = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(),lat[start}, lon[start]);
    double courseToDestination = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), lat[start], lon[start]);
    const char *directionToDestination = TinyGPSPlus::cardinal(courseToDestination);
    int courseChangeNeeded = (int)(360 + courseToDestination - gps.course.deg()) % 360;
   
    if (distanceToDestination <=1.0)
    {
      Serial.println("CONGRATULATIONS: You've arrived!");
      Stop();
      delay(30000);
    }

    Serial.print("DISTANCE: ");
    Serial.print(distanceToDestination);


    if (courseChangeNeeded >= 345 && courseChangeNeeded < 15)      
      if(distanceToDestination<6.0)
      Forward(speedlow);
      else
      forward(speedhigh);
      
    else if (courseChangeNeeded >= 315 && courseChangeNeeded < 345)       
      left(speedlow);    
    else if (courseChangeNeeded >= 15 && courseChangeNeeded < 45)       
     right(speedlow);
    else if (courseChangeNeeded >= 255 && courseChangeNeeded < 315)       
      left(speedhigh);     
    else if (courseChangeNeeded >= 45 && courseChangeNeeded < 105)
      right(speedHigh);
    else
      right(speedHigh);

    
  }
   start++; 
  }
  Serial.println("all point completed");
}
