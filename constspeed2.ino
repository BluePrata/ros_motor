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
std_msgs::UInt16 cmd_msg;
std_msgs::UInt16 motor_msg;
std_msgs::String string_msg;

int stage1 = 0;
int stage2 = 200;
int stage3 = 400;

int current_stage;
int current_step;

int toGo[2]; //direction, required steps

void check_stage(int stage)
{
   
   //compare current satge with desired stage
   if (stage < current_stage)
   {
      int direction = 0;
   }
   else
   {
      direction = 1;
   }
   int diff = abs(stage - current_stage);
   
   toGo[0] = direction;
   toGo[1] = diff*200;
   motorPub.publish(&int_msg);
	
   return toGo[2];
}

void current_stage()
{
   current_step=stepper.currentPosition().data;
   if (current_step <0)
   {
      current_step = 0;
   }
   if (current_step == 0) 
   {
      current_stage = 1;
   }
   if (current_step == 200)
   {
      current_stage = 2;
   }
   if (current_step == 400)
   {
      current_stage = 3;
   }

   return current_stage;       
 
}
//callback function to set stage (1-3)
void MotorCb ( Const std_msgs::UInt16& motor_msg) 
{
   desired_stage = motor_msg.data;   
   check_stage(desired_stage);
   digitalWrite(dir, toGo[0]);
   for(int x = 0; x < toGo[1]; x ++)
   {
      digitalWrite(stp, 1);
      delay(1);
      digitalwrite(stp, 0);		
      delay(1);
      if (x == toGo[1] - 1)
      {
         motor_msg.data = 999;
	 motor_state.publish(&motor_msg);       
      }
    }
}


ros::NodeHandle nh;
ros::Publisher motorPub("Motor", &int_msg);
ros::Subscriber<std_msgs::UInt16> motorSub("controlMotor", MotorCb);
ros::Publisher motor_state("MotorState", &motor_msg);

void setup()
{  
   stepper.setSpeed(550);	
   nh.advertise(motorPub);
   nh.subscribe(motorSub);
   nh.advertise(motor_state);
}

void loop()
{  
   nh.initNode();
   stepper.runSpeed();

//   current_step=stepper.currentPosition().data;
   
//   motorPub.publish(&int_msg);
   nh.spinOnce();
   delay(1);

}
