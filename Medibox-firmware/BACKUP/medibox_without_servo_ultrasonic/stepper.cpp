#include "Arduino.h"
#include "stepper.h"


Stepper::Stepper(int steps_number,int input1,int input2,int input3,int input4)
{
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);
  number_of_steps=steps_number;
  _last_step_time=0;
  _steps=0;
  _IN1=input1;
  _IN2=input2;
  _IN3=input3;
  _IN4=input4;
}

void Stepper::clockwise(){
  switch(Steps){
     case 0:
       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, HIGH);
     break;
     case 1:
       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, HIGH);
       digitalWrite(_IN4, HIGH);
     break;
     case 2:
       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, HIGH);
       digitalWrite(_IN4, LOW);
     break;
     case 3:
       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, HIGH);
       digitalWrite(_IN3, HIGH);
       digitalWrite(_IN4, LOW);
     break;
     case 4:
       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, HIGH);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);
     break;
     case 5:
       digitalWrite(_IN1, HIGH);
       digitalWrite(_IN2, HIGH);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);
     break;
       case 6:
       digitalWrite(_IN1, HIGH);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);
     break;
     case 7:
       digitalWrite(_IN1, HIGH);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, HIGH);
     break;
     default:
       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);

     break;
  }
  if(Direction){
    Steps++;
    Serial.println(Steps);
  }
  else{
    Steps--;
  }
  if(Steps>7){
    Steps=0;
    ISR=0;
  }
  if(Steps<0){
    Steps=7;
  }
}
void Stepper::clockwiseTime(){
  switch(Steps){
     case 0:
     if(count <runTime)
   	{
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, LOW);
        digitalWrite(_IN3, LOW);
        digitalWrite(_IN4, HIGH);
   	}else{
   		  stop_motor();
   	}
     break;
     case 1:
     if(count <runTime)
     {
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, LOW);
        digitalWrite(_IN3, HIGH);
        digitalWrite(_IN4, HIGH);
      }else{
		    stop_motor();
	  }

     break;
     case 2:
     if(count <runTime)
     {

       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, HIGH);
       digitalWrite(_IN4, LOW);
     }else{
       stop_motor();
    }
     break;
     case 3:
     if(count <runTime)
     {

       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, HIGH);
       digitalWrite(_IN3, HIGH);
       digitalWrite(_IN4, LOW);
     }else{
       stop_motor();
    }
     break;
     case 4:
     if(count <runTime)
     {

       digitalWrite(_IN1, LOW);
       digitalWrite(_IN2, HIGH);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);
     }else{
       stop_motor();
    }
     break;
     case 5:
     if(count <runTime)
     {

       digitalWrite(_IN1, HIGH);
       digitalWrite(_IN2, HIGH);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);
     }else{
       stop_motor();
    }
     break;
       case 6:
       if(count <runTime)
       {

       digitalWrite(_IN1, HIGH);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, LOW);
     }else{
       stop_motor();
    }
     break;
     case 7:
     if(count <runTime)
     {

       digitalWrite(_IN1, HIGH);
       digitalWrite(_IN2, LOW);
       digitalWrite(_IN3, LOW);
       digitalWrite(_IN4, HIGH);
     }else{
       stop_motor();
      }
     break;
     default:
      stop_motor();// stop the motor

     break;
  }
  if(Direction){
    Steps++;
  }
  else{
    Steps--;
  }
  if(Steps>7){
    Steps=0;
    //ISR=0;
  }
  if(Steps<0){
    Steps=7;
  }
  delay(1);

// check if the counter has reached run time
if(count < runTime){
   count++;//increment count
}else{
   count =0;// set to zero
}
}
void Stepper::stop_motor(){
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);
  if(ISR==1){
      ISR=0;
  }

}
void Stepper::setSpeed(long whatSpeed){
  _step_delay = 60L * 1000L / number_of_steps / whatSpeed;

}
void Stepper::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
  if(steps_to_move>0){
    Direction=1;
  }
  if(steps_to_move<0){
    Direction=0;
  }
  while(steps_left>0){
    //move if proper delay is passed
    if(millis()-_last_step_time >=_step_delay){
      _last_step_time=millis();
      if(Direction){
        _steps++;
        Serial.println(_steps);
        if(_steps==steps_to_move){
          _steps=0;
          ISR=0;
        }
      }
      steps_left--;
      //Serial.println(steps_left);
      stepMotor(_steps % 4);
    }

  }

}
void Stepper::stepMotor(int thisStep){
  switch (thisStep) {
  case 0:    // 1000
  digitalWrite(_IN1, HIGH);//these are modified for the Arduino Kit geared stepper motor
  digitalWrite(_IN2, LOW);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW);
  break;
  case 1:    // 0100
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, LOW);
  break;
  case 2:    //0010
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
  break;
  case 3:    //0001
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH);
  break;
}
}
