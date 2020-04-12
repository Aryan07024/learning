





#include "Wire.h"
 #include <ros.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>


std_msgs::String imu_msg;
ros::Publisher imu("imu", &imu_msg);


MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
//     nh.initNode();
 // nh.advertise(imu);
}

void loop() {
   
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

   

    // display tab-separated accel/gyro x/y/z values
    String axs = String(ax);
    String ays = String (ay);
    String azs = String (az);
    String gxs = String (gx);
    String gys = String (gy);
    String gzs = String (gz);
    String mxs = String (mx);
    String mys = String (my);
    String mzs = String (mz);
        
    String data ="Ax"+axs+"Ay"+ays+"Az"+azs+"Gx"+gxs+"Gy"+gys+"Gz"+gzs+"Mx"+mxs+"My"+mys+"Mz"+mzs+"Z";
    int length = data.indexOf("Z") +2;
    char info[length+1];
    data.toCharArray(info, length+1);

  imu_msg.data=info;
  imu.publish( &imu_msg );
 // nh.spinOnce();
  delay(100);

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
