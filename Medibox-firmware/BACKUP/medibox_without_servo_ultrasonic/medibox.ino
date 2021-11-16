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

void setup(){
  //setup rtc
  //motor
  //esp8266

  Serial.begin(9600);
  rotate.setSpeed(0.15*gearratio);

  pinMode(rtc_interruptPin, INPUT_PULLUP);
  rtc.begin();
  #ifdef DEBUG
    Serial.begin(9600);
    delay(10);
    Serial.println("MediBox is Ready");
  #endif
  //rotate.step(500);
  //delay(500);
//mySerial.WiFiConnect("cyber_crime","polyandros");
//attachInterrupt(digitalPinToInterrupt(rtc_interruptPin), Isr_Int, FALLING);
//rtc.clearINTStatus();
//rtc.enableInterrupts(13,17, 0);

}

void loop(){
  Serial.println("clockwise");
rotate.step(73);
delay(500);

  /*t = rtc.getTime();
  if(t.min >17 && inter==1){
    rtc.clearINTStatus();
    Serial.println("New Alarm Set");
    rtc.enableInterrupts(13,18,10);
    inter=0;
  }
//rotate.clockwise();
  //despense medicine depends upon rtc
  // Send Day-of-Week
  //  Serial.print(rtc.getDOWStr());
  //  Serial.print(" ");

    // Send date
    //Serial.print(rtc.getDateStr());
    //Serial.print(" -- ");

    // Send time
    //Serial.println(rtc.getTimeStr());

    // Wait one second before repeating :)
    //delay (1000);
    //rotations();
    //rotate.clockwise();
    while(rotate.ISR==1){
    Serial.print("Executing ISR");
      rotate.step(500);
      //delay(500);
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
