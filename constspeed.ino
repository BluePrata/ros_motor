//this file has wrong checksum for topic id and msg

#if (ARDUINO >=100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <ros/time.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>

#include <AccelStepper.h>

AccelStepper stepper(4,22,23,19,20); // Defaults to 4 pins on 2, 3, 4, 5

std_msgs::UInt16 int_msg;
ros::NodeHandle nh;
ros::Publisher motorPub("Motor", &int_msg);

void setup()
{  
   stepper.setSpeed(550);	
   nh.advertise(motorPub);
}

void loop()
{  
   nh.initNode();
   stepper.runSpeed();

   int_msg.data=stepper.currentPosition();
   motorPub.publish(&int_msg);
   nh.spinOnce();
   delay(1);
//   delay(1000);
}
