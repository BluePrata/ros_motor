#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <ros/time.h>
#include <math.h>
#include <std_msgs/String.h>

//Stepper Motor header
#include <AccelStepper.h>

//Ultrasonic sensor header
#include <sensor_msgs/Range.h>
sensor_msgs::Range range_msg;

//Servo header
#include <Servo.h>
Servo mysevo;

#define stp 22
#define dir 23
#define MS1 19
#define MS2 20
#define MS3 21
#define EN 18

#define servo_pin 9;

ros::NodeHandle nh;

ros::Publisher ultra_pub("ToBox_xpos", &range_msg);
ros::Subscriber<std_msgs::UInt16> servo_sub("servoPos", servoCallback);

const int adc_pin = 0;
char frameid[] = "ToBox_xpos";

int step_1 = 10; //to be adjusted
int step_2 = 20;
int step_3 = 30;

float getRange_Ultrasound(int pin_num){
  int val = 0;
  for(int i=0; i<4; i++) val += analogRead(pin_num);
  float range = val;
  return range /332.519685;
}


typedef struct
{
  double x_range; //Ultrasonic range
  Boolean y_range = false; //switch 1 - closed
  int servo_pos; //servo position
  Boolean servo_flag = false;
  long range_time;
}

void setup()
{
  myservo.attach(servo_pin;

  nh.initNode();

  nh.advertise(ultra_pub);
  nh.subscribe(servo_sub);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 6.47;

  pinMode(8,OUTPUT);
  digitalWrite(8, LOW);

  //Stepper Motor
  pinMode(stp, OUTPUT);	
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);

}

void loop()
{
  if ( millis() >= range_time ){
    int r =0;

    range_msg.range = getRange_Ultrasound(5);
    range_msg.header.stamp = nh.now();
    ultra_pub.publish(&range_msg);
    range_time =  millis() + 50;
  }

  nh.spinOnce();
  delay(1);
}

void swtich()
{
  int switchArray[4] = {0,0,0,0};
  for (int i=0; i<4; i++)
  {
    switchArray[i]=digitalRead[i+5]; //switch 5,6,7,8
    //for mechanical debugging
    if(switchArray[i] !== 1 )
    {
      Serial.print("Switch "); Serial.print(i);Serial.println(" :not detected");
    }
    int arraySum += switchArray[i];
    if(arraySum == 4)
    {
      Serial.println("Gripper closed fully");
      return y_range = true;
    }
    if(arraySum <4)
    {
      Serial.println("Gripper NOT closed fully");
      return y_range = false;
    }
  }
}

void servoCallback(const std_msgs::UInt16& cmd_servo)
{
  servo.write(cmd_servo.data);
}


// void move_servo(Boolean ..., int position)
// {
//   if(servo_flag == true){
//
//   }
// }


//Stepper Motor

void stage(Stage)
{
  digitalWrite(dir, LOW); 
  
  	
	 
	
}
void stage_1()
{
  digitalWrite(dir, LOW)
  for (int step = 1; step < step_1; x++) 
	{
	  digitalWrite(stp, HIGH);
          delay(1);
          digitalWrite(stp, LOW);
          delay(1);
	}
}

void stage_2()
{

}

void stage_3()
{

}
