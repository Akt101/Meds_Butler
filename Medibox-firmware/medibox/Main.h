#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "pins.h"
#include "stepper.h"
//#include "esp8266.h"
#include <SoftwareSerial.h>
#include <DS3231.h>
#include <Servo.h>
#include <IRremote.h>
DS3231  rtc(SDA, SCL);
Servo Servo1;
Time  t;
int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;
