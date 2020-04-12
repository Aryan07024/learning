
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include<ros.h>
#include <sensor_msgs/Imu.h>

ros::NodeHandle nh;
sensor_msgs::Imu imu_msg;
ros::Publisher imu_data("/imu_data", &imu_msg);


MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    
    Wire.begin();

    
    Serial.begin(38400);

   
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

   
    pinMode(LED_PIN, OUTPUT);
    nh.initNode();
    nh.advertise(imu_data);
}
void PublishImuData()
{

        accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    
           
        imu_msg.orientation.w = 0;      //29789.09091
        imu_msg.orientation.x = gx;
        imu_msg.orientation.y = gy;
        imu_msg.orientation.z = gz;

        
        imu_msg.angular_velocity.x = mx;
        imu_msg.angular_velocity.y = my;
        imu_msg.angular_velocity.z = mz;

      
        imu_msg.linear_acceleration.x = ax;
        imu_msg.linear_acceleration.y = ay;
        imu_msg.linear_acceleration.z = az;

        imu_data.publish(&imu_msg);        
    }


void loop() {
     PublishImuData();
     nh.spinOnce();
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
