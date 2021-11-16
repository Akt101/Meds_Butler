/*
* Ultrasonic Sensor HC-SR04 interfacing with Arduino.
*/
// defining the pins
#include <DS3231.h>
#include <Servo.h> 
DS3231  rtc(SDA, SCL);
// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
Servo Servo1; 
const byte rtc_interruptPin = 2;
bool ISR=0;
// defining variables
int obstacle= 7;
int obstacleCheck= HIGH;
void setup() {
Servo1.attach(servoPin); 
Serial.begin(9600); // Starts the serial communication
 pinMode(obstacle,INPUT);
pinMode(rtc_interruptPin, INPUT_PULLUP);
rtc.begin();
Servo1.write(0); 
delay(1000);
attachInterrupt(digitalPinToInterrupt(rtc_interruptPin), Isr_Int, FALLING);
rtc.clearINTStatus();
rtc.enableInterrupts(13,15, 0);
}
void loop() {

obstacleCheck= digitalRead(obstacle);
if(ISR==1 && obstacleCheck==LOW){
  Serial.print("Despensing...");
   Servo1.write(90); 
   delay(1000);
   Servo1.write(0); 
   delay(1000); 
   ISR=0;

}
}
void Isr_Int(){
  Serial.println("Interrupt Service Routine Called");
ISR=1;
//delayMicroseconds(5000);
}

