#include "Main.h"
#define DEBUG
int IN1=8;
int IN2=9;
int IN3=10;
int IN4=11;
#define gearratio 64
Stepper rotate(2048,8,9,10,11);
bool inter=1;
Esp8266 mySerial(4,3);
const byte rtc_interruptPin = 2;
const int trigPin = 12;
const int echoPin = 13;
long duration;
int distance;
int count=0;
int servoPin = 5;
int th1=17;
int tmin1=22;
int tsec1=0;
int th2=17;
int tmin2=22;
int tsec2=30;
int th3=17;
int tmin3=23;
int tsec3=0;
int th4=17;
int tmin4=23;
int tsec4=30;
int th5=17;
int tmin5=24;
int tsec5=0;

void setup(){
  //setup rtc
  //motor
  //esp8266

  Serial.begin(9600);
/*
  rotate.setSpeed(0.15*gearratio);

  pinMode(rtc_interruptPin, INPUT_PULLUP);
  rtc.begin();
  #ifdef DEBUG
    Serial.begin(9600);
    delay(10);
    Serial.println("MediBox is Ready");
  #endif
  Servo1.attach(servoPin);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //rotate.step(500);
  delay(500);*/
mySerial.WiFiConnect("cyber_crime","polyandros");

/*Servo1.write(0);
attachInterrupt(digitalPinToInterrupt(rtc_interruptPin), Isr_Int, FALLING);
rtc.clearINTStatus();
rtc.enableInterrupts(th1,tmin1,tsec1);
*/
}

void loop(){

/*  t = rtc.getTime();
  Serial.print("hour");
  Serial.println(t.hour);
  Serial.println(t.min);

  if( t.min >= tmin1 && t.hour>=th1 && t.sec> tsec1 && count==0){
    count=count+1;
    rtc.clearINTStatus();
    Serial.println("Alarm 2 Set");
    rtc.enableInterrupts(th2,tmin2,tsec2);
  }
  if( t.min >= tmin2 && t.hour >=th2 && t.sec> tsec2 && count==1){
    count=count+1;
    rtc.clearINTStatus();
    Serial.println(" Alarm 3 Set");
    rtc.enableInterrupts(th3,tmin3,tsec3);
  }
  if( t.min >= tmin3 && t.hour >=th3 && t.sec> tsec3 && count==2){
    count=count+1;
    rtc.clearINTStatus();
    Serial.println(" Alarm 4 Set");
    rtc.enableInterrupts(th4,tmin4,tsec4);
  }
  if( t.min >= tmin4 && t.hour >=th4 && t.sec> tsec4 && count==3){
    count=count+1;
    rtc.clearINTStatus();
    Serial.println(" Alarm 5 Set");
    rtc.enableInterrupts(th5,tmin5,tsec5);
  }

  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;

    while(rotate.ISR==1){
    Serial.print("Executing ISR");
      rotate.step(200);
    }
    if(rotate.SERVO==1 && distance <4){
      Serial.print("Distance: ");
      Serial.println(distance);
      Servo1.write(90);
      delay(1000);
      Servo1.write(0);
      delay(1000);
      rotate.SERVO=0;
    }
*/
}

void Isr_Int(){
  Serial.println("Interrupt Service Routine Called");
rotate.ISR=1;
//delayMicroseconds(5000);
}
void rotations(){
  if(rotate.ISR==1){
    Serial.println("Executing ISR");
    rotate.clockwise();
  }
  if(rotate.ISR==1){
    rotate.ISR=0;
  }
}
