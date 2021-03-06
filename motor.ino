#if (ARDUINO >=100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <ros/time.h>

ros::NodeHandle nh;

#include <AccelStepper.h>

#define stp 22
#define dir 23
#define MS1 19
#define MS2 20
#define MS3 21
#define EN 18


char user_input;
int x;

AccelStepper stepper_pulley(22,23,19,20);

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

  //stepper_pulley.setSpeed(50);	
  //stepper_pulley.setAcceleration(10);	
  //digitalWrite(EN, LOW); 
  //stepper.moveTo(45);	
}

void loop() 
{
	nh.initNode();
	//stepper.run();
	

	digitalWrite(EN, LOW);
	//digitalWrite(dir, HIGH);
	//stepper.runSpeed();
	//stepper_pulley.moveTo(90); 	
	//stepper_pulley.run();	
	StepForwardDefault();
	delay(7000);
	ReverseStepDefault();
	delay(7000);
}


void StepForwardDefault()
{

  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<400; x++)  //Loop the forward stepping enough times for motion to be visible
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
  for(x= 1; x<400; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

}

