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
const int trigPin = 9;
const int echoPin = 10;
const byte rtc_interruptPin = 2;
bool ISR=0;
// defining variables
long duration;
int distance;
void setup() {
Servo1.attach(servoPin); 
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
pinMode(rtc_interruptPin, INPUT_PULLUP);
rtc.begin();
Servo1.write(0); 
delay(1000);
attachInterrupt(digitalPinToInterrupt(rtc_interruptPin), Isr_Int, FALLING);
rtc.clearINTStatus();
rtc.enableInterrupts(11,52, 0);
}
void loop() {
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
// Prints the distance on the Serial Monitor

if(ISR==1 && distance <4){
  Serial.print("Distance: ");
  Serial.println(distance);
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

