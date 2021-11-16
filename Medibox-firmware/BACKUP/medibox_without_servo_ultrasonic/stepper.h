/*
  Stepper.h - Library for rotation of stepper motor.
  Created by Akshay Konde, April 27, 2018.
*/
#ifndef Stepper_h
#define Stepper_h

#include "Arduino.h"
#include "pins.h"
class Stepper
{
  public:
    Stepper(int steps_number,int input1,int input2,int input3,int input4);
    void stop_motor();
    void clockwise();
    void anticlockwise();
    void clockwiseTime();
    void step(int number_of_steps);
    void setSpeed(long whatSpeed);
    bool Direction =1;
    int Steps=0;
    bool ISR=0;
  private:
    int _IN1,_IN2,_IN3,_IN4;
    int _steps;
    int count=0;// counter for running time
    int runTime = 3000;// the time motor will run
    long _step_delay;
    int _last_step_time;
    int number_of_steps;
    void stepMotor(int this_step);



};

#endif
