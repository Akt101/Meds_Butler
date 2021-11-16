#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "pins.h"
#include "stepper.h"
#include "esp8266.h"
#include <SoftwareSerial.h>
#include <DS3231.h>
DS3231  rtc(SDA, SCL);
Time  t;
