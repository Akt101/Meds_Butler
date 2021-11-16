#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Wire.h>
#include <RtcDS3231.h>
const byte interruptPin = 13;
const byte motorPin = 15;
volatile bool alarm = 0;
bool flag=0;
RtcDS3231<TwoWire> rtcObject(Wire);
// WiFi Parameters
/*const char* ssid = "esp8266";
const char* password = "akshayk23";*/
int th1,tm1,th2,tm2, th3, tm3,th4,tm4,th5,tm5,th6,tm6,th7,tm7,th8,tm8,th9,tm9,th10,tm10,th11,tm11,th12,tm12;
int th13,tm13,th14,tm14,th15,tm15,th16,tm16,th17,tm17,th18,tm18,th19,tm19,th20,tm20,th21,tm21,th22,tm22;
int th23,tm23,th24,tm24,th25,tm25,th26,tm26,th27,tm27,th28,tm28,c_date,c_month,c_year,c_hour,c_minute;
int count=0;
int I2C_ClearBus() {
#if defined(TWCR) && defined(TWEN)
  TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
#endif
  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);

  delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
  // up of the DS3231 module to allow it to initialize properly,
  // but is also assists in reliable programming of FioV3 boards as it gives the
  // IDE a chance to start uploaded the program
  // before existing sketch confuses the IDE by sending Serial data.

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master.
    return 1; //I2C bus error. Could not clear SCL clock line held low
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
  // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
      return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
    return 3; // I2C bus error. Could not clear. SDA data line held low
  }

  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  return 0; // all ok
}
void setup() {
  Serial.begin(19200);
  int rtn = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
  if (rtn != 0) {
    Serial.println(F("I2C bus error. Could not clear"));
    if (rtn == 1) {
      Serial.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      Serial.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      Serial.println(F("SDA data line held low"));
    }
  } else { // bus clear
    // re-enable Wire
    // now can start Wire Arduino master
    Wire.begin();
  }
  Serial.println("setup finished");
  rtcObject.Begin();
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

  RtcDateTime timestamp = RtcDateTime(__DATE__, __TIME__);
  //rtcObject.SetDateTime(timestamp);
  rtcObject.Enable32kHzPin(false);
  rtcObject.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmOne);
   WiFiManager wifiManager;
   wifiManager.autoConnect("MediWatch");
   /*DS3231AlarmOne alarm1(
  7,
  23,
  19,
  0,
  DS3231AlarmOneControl_HoursMinutesSecondsMatch);

rtcObject.SetAlarmOne(alarm1);
rtcObject.LatchAlarmsTriggeredFlags();*/
}

void loop() {
  RtcDateTime currentTime = rtcObject.GetDateTime();
  if (alarm == true) {
    handleAlarm();
  }
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED && flag==0) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://mediboard.sumeetgohil.com/api/slots/1");
    int httpCode = http.GET();
    //Check the returning code
    if (httpCode > 0) {
      // Get the request response payload
      //String payload = http.getString();
      // TODO: Parsing
      const size_t bufferSize = JSON_OBJECT_SIZE(54) + 550;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      const char* thr1 = root["thr1"]; // "10"
      const char* tmin1 = root["tmin1"]; // "00"
      const char* thr2 = root["thr2"]; // "11"
      const char* tmin2 = root["tmin2"]; // "00"
      const char* thr3 = root["thr3"]; // "12"
      const char* tmin3 = root["tmin3"]; // "30"
      const char* thr4 = root["thr4"]; // "13"
      const char* tmin4 = root["tmin4"]; // "50"
      const char* thr5 = root["thr5"]; // "10"
      const char* tmin5 = root["tmin5"]; // "00"
      const char* thr6 = root["thr6"]; // "11"
      const char* tmin6 = root["tmin6"]; // "00"
      const char* thr7 = root["thr7"]; // "12"
      const char* tmin7 = root["tmin7"]; // "30"
      const char* thr8 = root["thr8"]; // "13"
      const char* tmin8 = root["tmin8"]; // "50"
      const char* thr9 = root["thr9"]; // "10"
      const char* tmin9 = root["tmin9"]; // "00"
      const char* thr10 = root["thr10"]; // "11"
      const char* tmin10 = root["tmin10"]; // "00"
      const char* thr11 = root["thr11"]; // "12"
      const char* tmin11 = root["tmin11"]; // "30"
      const char* thr12 = root["thr12"]; // "13"
      const char* tmin12 = root["tmin12"]; // "50"
      const char* thr13 = root["thr13"]; // "10"
      const char* tmin13 = root["tmin13"]; // "00"
      const char* thr14 = root["thr14"]; // "11"
      const char* tmin14 = root["tmin14"]; // "00"
      const char* thr15 = root["thr15"]; // "12"
      const char* tmin15 = root["tmin15"]; // "30"
      const char* thr16 = root["thr16"]; // "13"
      const char* tmin16 = root["tmin16"]; // "50"
      const char* thr17 = root["thr17"]; // "10"
      const char* tmin17 = root["tmin17"]; // "00"
      const char* thr18 = root["thr18"]; // "11"
      const char* tmin18 = root["tmin18"]; // "00"
      const char* thr19 = root["thr19"]; // "12"
      const char* tmin19 = root["tmin19"]; // "30"
      const char* thr20 = root["thr20"]; // "13"
      const char* tmin20 = root["tmin20"]; // "50"
      const char* thr21 = root["thr21"]; // "10"
      const char* tmin21 = root["tmin21"]; // "00"
      const char* thr22 = root["thr22"]; // "11"
      const char* tmin22 = root["tmin22"]; // "00"
      const char* thr23 = root["thr23"]; // "12"
      const char* tmin23 = root["tmin23"]; // "30"
      const char* thr24 = root["thr24"]; // "10"
      const char* tmin24 = root["tmin24"]; // "00"
      const char* thr25 = root["thr25"]; // "11"
      const char* tmin25 = root["tmin25"]; // "00"
      const char* thr26 = root["thr26"]; // "12"
      const char* tmin26 = root["tmin26"]; // "30"
      const char* thr27 = root["thr27"]; // "13"
      const char* tmin27 = root["tmin27"]; // "50"
      const char* thr28 = root["thr28"]; // "13"
      const char* tmin28 = root["tmin28"]; // "50"
      const char* current_date= root["current_date_day"];
      const char* current_month=root["current_date_month"];
      const char* current_year=root["current_date_year"];
      const char* current_hour=root["current_time_hr"];
      const char* current_minute=root["current_time_min"];

      th1= atoi(thr1);
      tm1= atoi(tmin1);
      th2= atoi(thr2);
      tm2= atoi(tmin2);
      th3= atoi(thr3);
      tm3= atoi(tmin3);
      th4= atoi(thr4);
      tm4= atoi(tmin4);
      th5= atoi(thr5);
      tm5= atoi(tmin5);
      th6= atoi(thr6);
      tm6= atoi(tmin6);
      th7= atoi(thr7);
      tm7= atoi(tmin7);
      th8= atoi(thr8);
      tm8= atoi(tmin8);
      th9= atoi(thr9);
      tm9= atoi(tmin9);
      th10= atoi(thr10);
      tm10= atoi(tmin10);
      th11= atoi(thr11);
      tm11= atoi(tmin11);
      th12= atoi(thr12);
      tm12= atoi(tmin12);
      th13= atoi(thr13);
      tm13= atoi(tmin13);
      th14= atoi(thr14);
      tm14= atoi(tmin14);
      th15= atoi(thr15);
      tm16= atoi(tmin16);
      th17= atoi(thr17);
      tm17= atoi(tmin17);
      th18= atoi(thr18);
      tm18= atoi(tmin18);
      th19= atoi(thr19);
      tm19= atoi(tmin19);
      th20= atoi(thr20);
      tm20= atoi(tmin20);
      th21= atoi(thr21);
      tm21= atoi(tmin21);
      th22= atoi(thr22);
      tm22= atoi(tmin22);
      th23= atoi(thr23);
      tm23= atoi(tmin23);
      th24= atoi(thr24);
      tm24= atoi(tmin24);
      th25= atoi(thr25);
      tm25= atoi(tmin25);
      th26= atoi(thr26);
      tm26= atoi(tmin26);
      th27= atoi(thr27);
      tm27= atoi(tmin27);
      th28= atoi(thr28);
      tm28= atoi(tmin28);
      c_date=atoi(current_date);
      c_month=atoi(current_month);
      c_year= atoi(current_year);
      c_hour= atoi(current_hour);
      c_minute= atoi(current_minute);
      Serial.print("current_date:");
      Serial.println(c_date);
      Serial.print("current_month:");
      Serial.println(c_month);
      Serial.print("current_year:");
      Serial.println(c_year);
      Serial.print("current_hour:");
      Serial.println(c_hour);
      Serial.print("current_minute:");
      Serial.println(c_minute);
    /*  Serial.println(thr2);
      delay(100);
      Serial.println(tmin2);
      delay(100);
      Serial.println(thr3);
      delay(100);
      Serial.println(tmin3);
      delay(100);
      Serial.println(thr4);
      delay(100);
      Serial.println(tmin4);
      delay(100);
      Serial.println(thr5);
      delay(100);
      Serial.println(tmin5);
      delay(100);
      Serial.println(thr6);
      delay(100);
      Serial.println(tmin6);
      delay(100);
      Serial.println(thr7);
      delay(100);
      Serial.println(tmin7);
      delay(100);
      Serial.println(thr8);
      delay(100);
      Serial.println(tmin8);
      delay(100);
      Serial.println(thr9);
      delay(100);
      Serial.println(tmin9);
      delay(100);
      Serial.println(thr10);
      delay(100);
      Serial.println(tmin10);
      delay(100);
      Serial.println(thr11);
      delay(100);
      Serial.println(tmin11);
      delay(100);
      Serial.println(thr12);
      delay(100);
      Serial.println(tmin12);
      delay(100);
      Serial.println(thr13);
      delay(100);
      Serial.println(tmin13);
      delay(100);
      Serial.println(thr14);
      delay(100);
      Serial.println(tmin14);
      delay(100);
      Serial.println(thr15);
      delay(100);
      Serial.println(tmin15);
      delay(100);
      Serial.println(thr16);
      delay(100);
      Serial.println(tmin16);
      delay(100);
      Serial.println(thr17);
      delay(100);
      Serial.println(tmin17);
      delay(100);
      Serial.println(thr18);
      delay(100);
      Serial.println(tmin18);
      delay(100);
      Serial.println(thr19);
      delay(100);
      Serial.println(tmin19);
      delay(100);
      Serial.println(thr20);
      delay(100);
      Serial.println(tmin20);
      delay(100);
      Serial.println(thr21);
      delay(100);
      Serial.println(tmin21);
      delay(100);
      Serial.println(thr22);
      delay(100);
      Serial.println(tmin22);
      delay(100);
      Serial.println(thr23);
      delay(100);
      Serial.println(tmin23);
      delay(100);
      Serial.println(thr24);
      delay(100);
      Serial.println(tmin24);
      delay(100);
      Serial.println(thr25);
      delay(100);
      Serial.println(tmin25);
      delay(100);
      Serial.println(thr26);
      delay(100);
      Serial.println(tmin26);
      delay(100);
      Serial.println(thr27);
      delay(100);
      Serial.println(tmin27);
      delay(100);*/
    }
    http.end();   //Close connection
    flag=1;
  }
Serial.print("day=");
Serial.println(currentTime.Day());
Serial.print("hour=");
Serial.println(currentTime.Hour());
Serial.print("minute=");
Serial.println(currentTime.Minute());
Serial.print("seconds=");
Serial.println(currentTime.Second());
Serial.print("Weekday=");
Serial.println(currentTime.DayOfWeek());
delay(1000);
//Monday
  if(currentTime.DayOfWeek()==1){
    count==0;
    if(count==0){
        DS3231AlarmOne alarm1(
        1,
        th1,
        tm1,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
      }
    if(count==1 && currentTime.Hour()>=th1 && currentTime.Minute() >=tm1 && currentTime.Second()>0 ){
        DS3231AlarmOne alarm1(
        1,
        th2,
        tm2,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
    }
    if(count==2 && currentTime.Hour()>= th2 && currentTime.Minute() >= tm2 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      1,
      th3,
      tm3,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
    if(count==3 && currentTime.Hour()>= th3 && currentTime.Minute() >= tm3 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      1,
      th4,
      tm4,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  }
  //Tuesday
  if(currentTime.DayOfWeek()==2){
    count==0;
    if(count==0){
        DS3231AlarmOne alarm1(
        2,
        th5,
        tm5,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
      }
    if(count==1 && currentTime.Hour()>=th5 && currentTime.Minute() >=tm5 && currentTime.Second()>0 ){
        DS3231AlarmOne alarm1(
        2,
        th6,
        tm6,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
    }
    if(count==2 && currentTime.Hour()>= th6 && currentTime.Minute() >= tm6 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      2,
      th7,
      tm7,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
    if(count==3 && currentTime.Hour()>= th7 && currentTime.Minute() >= tm7 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      2,
      th8,
      tm8,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  }
  //Wednesday
  if(currentTime.DayOfWeek()==3){
    count==0;
    if(count==0){
        DS3231AlarmOne alarm1(
        3,
        th9,
        tm9,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
      }
    if(count==1 && currentTime.Hour()>=th9 && currentTime.Minute() >=tm9 && currentTime.Second()>0 ){
        DS3231AlarmOne alarm1(
        3,
        th10,
        tm10,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
    }
    if(count==2 && currentTime.Hour()>= th10 && currentTime.Minute() >= tm10 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      3,
      th11,
      tm11,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
    if(count==3 && currentTime.Hour()>= th11 && currentTime.Minute() >= tm11 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      3,
      th12,
      tm12,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  }
  //Thursday
  if(currentTime.DayOfWeek()==4){
    count==0;
    Serial.println(count);
    if(count==0){
        DS3231AlarmOne alarm1(
        4,
        th13,
        tm13,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
      }
    if(count==1 && currentTime.Hour()>=th13 && currentTime.Minute() >=tm13 && currentTime.Second()>0 ){
        DS3231AlarmOne alarm1(
        4,
        th14,
        tm14,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
    }
    if(count==2 && currentTime.Hour()>= th14 && currentTime.Minute() >= tm14 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      4,
      th15,
      tm15,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
    if(count==3 && currentTime.Hour()>= th15 && currentTime.Minute() >= tm15 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      4,
      th16,
      tm16,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  }
  //Friday
  if(currentTime.DayOfWeek()==5){
    count==0;
    Serial.println(count);
    if(count==0){
        DS3231AlarmOne alarm1(
        5,
        th17,
        tm17,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
      }
    if(count==1 && currentTime.Hour()>=th17 && currentTime.Minute() >=tm17 && currentTime.Second()>0 ){
        DS3231AlarmOne alarm1(
        5,
        th18,
        tm18,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
    }
    if(count==2 && currentTime.Hour()>= th18 && currentTime.Minute() >= tm18 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      5,
      th19,
      tm19,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
    if(count==3 && currentTime.Hour()>= th19 && currentTime.Minute() >= tm19 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      5,
      th20,
      tm20,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  }
  //Saturday
  if(currentTime.DayOfWeek()==6){
    count==0;
    Serial.println(count);
    if(count==0){
        DS3231AlarmOne alarm1(
        6,
        th21,
        tm21,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
      }
    if(count==1 && currentTime.Hour()>=th21 && currentTime.Minute() >=tm21 && currentTime.Second()>0 ){
        DS3231AlarmOne alarm1(
        6,
        th22,
        tm22,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
        rtcObject.SetAlarmOne(alarm1);
        rtcObject.LatchAlarmsTriggeredFlags();
        count=count+1;
    }
    if(count==2 && currentTime.Hour()>= th22 && currentTime.Minute() >= tm22 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      6,
      th23,
      tm23,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
    if(count==3 && currentTime.Hour()>= th23 && currentTime.Minute() >= tm23 && currentTime.Second()>0){
      DS3231AlarmOne alarm1(
      6,
      th24,
      tm24,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  }
if(currentTime.DayOfWeek()==0){
  count==0;
  Serial.println(count);
  if(count==0){
      DS3231AlarmOne alarm1(
      0,
      th25,
      tm25,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
    }
  if(count==1 && currentTime.Hour()>=th25 && currentTime.Minute() >=tm25 && currentTime.Second()>0 ){
      DS3231AlarmOne alarm1(
      0,
      th26,
      tm26,
      0,
      DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
      rtcObject.SetAlarmOne(alarm1);
      rtcObject.LatchAlarmsTriggeredFlags();
      count=count+1;
  }
  if(count==2 && currentTime.Hour()>= th26 && currentTime.Minute() >= tm26 && currentTime.Second()>0){
    DS3231AlarmOne alarm1(
    0,
    th27,
    tm27,
    0,
    DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
    rtcObject.SetAlarmOne(alarm1);
    rtcObject.LatchAlarmsTriggeredFlags();
    count=count+1;
  }
  if(count==3 && currentTime.Hour()>= th27 && currentTime.Minute() >= tm27 && currentTime.Second()>0){
    DS3231AlarmOne alarm1(
    0,
    th28,
    tm28,
    0,
    DS3231AlarmOneControl_HoursMinutesSecondsDayOfWeekMatch);
    rtcObject.SetAlarmOne(alarm1);
    rtcObject.LatchAlarmsTriggeredFlags();
    count=count+1;
  }
}
}
void handleAlarm() {
  alarm = false;
  Serial.println("yipeeeeee!");
  digitalWrite(motorPin, HIGH);
  delay(10000);
  digitalWrite(motorPin,LOW);
  rtcObject.LatchAlarmsTriggeredFlags();

}

void handleInterrupt() {
  alarm = true;
}
