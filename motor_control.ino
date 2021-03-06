#if (ARDUINO >=100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <ros/time.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

#include <AccelStepper.h>

#define stp 22
#define dir 23
#define MS1 19
#define MS2 20
#define MS3 21
#define EN 18


int x;

int current_stage;
int prev_stage;

AccelStepper stepper_pulley(4,22,23,19,20);
std_msgs::UInt16 int_msg;

//void StepForwardDefault();
//void ReverseStepDefault();


void StepForwardDefault()
{

  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<400; x++)  //Loop the forward stepping enough times for motion to$
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

}

//Reverse default microstep mode function
void ReverseStepDefault()
{
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<400; x++)  //Loop the stepping enough times for motion to be visi$
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

}

void MotorCb( const std_msgs::UInt16& motor_msg)
{
        int state = motor_msg.data;
        if (state == 1) {
                StepForwardDefault();

        }
        if (state == 2) {

                ReverseStepDefault();
        }
        int_msg.data = stepper_pulley.currentPosition();
}




ros::Subscriber<std_msgs::UInt16> motorSub("PulleyMotor", MotorCb);
ros::Publisher motorPub("MotorInfo", &int_msg);

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);


  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);

  prev_stage = 1;	
  nh.advertise(motorPub);
  nh.subscribe(motorSub);

  //stepper_pulley.setMaxSpeed(200.0);
  //stepper_pulley.setAcceleration(100.0);
  stepper_pulley.setSpeed(200);
  //stepper_pulley.moveTo(50);  
}

void loop() 
{
	nh.initNode();
	//stepper.run();

  //stepper_pulley.runToNewPosition(0);
  //stepper_pulley.runToNewPosition(134);
	stepper_pulley.runSpeed();	
        int_msg.data = stepper_pulley.currentPosition();

	digitalWrite(EN, LOW);
		
	//StepForwardDefault();
	//delay(7000);
	//ReverseStepDefault();
	//delay(7000);

	motorPub.publish(&int_msg);
	nh.spinOnce();
	delay(1000);


}


