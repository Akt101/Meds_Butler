#include "Main.h"
#define DEBUG
int IN1=8;
int IN2=9;
int IN3=11;
int IN4=12;
#define gearratio 64
Stepper rotate(2048,8,9,11,12);
bool inter=1;
bool flag=0;
String payload;
SoftwareSerial ESP_Serial(4,3);
const byte rtc_interruptPin = 2;
int count=0;
int servoPin = 5;
int obstacle= 7;
int obstacleCheck= HIGH;

int th1,tmin1,th2,tmin2, th3, tmin3,th4,tmin4,th5,tmin5,th6,tmin6,th7,tmin7,th8,tmin8,th9,tmin9,th10,tmin10,th11,tmin11,th12,tmin12;
int th13,tmin13,th14,tmin14,th15,tmin15,th16,tmin16,th17,tmin17,th18,tmin18,th19,tmin19,th20,tmin20,th21,tmin21,th22,tmin22;
int th23,tmin23,th24,tmin24,th25,tmin25,th26,tmin26,th27,tmin27,th28,tmin28,current_date,current_month,current_year,current_hour,current_minute;
void setup(){
  //setup rtc
  //motor
  //esp8266
  Serial.begin(115200);
  ESP_Serial.begin(19200);
  rotate.setSpeed(0.15*gearratio);

  pinMode(rtc_interruptPin, INPUT_PULLUP);
  rtc.begin();

  Servo1.attach(servoPin);
Servo1.write(0);
attachInterrupt(digitalPinToInterrupt(rtc_interruptPin), Isr_Int, FALLING);
rtc.clearINTStatus();
 irrecv.enableIRIn();
Serial.println("MediBox is Ready");
}
String ak;
void loop(){

  if (irrecv.decode(&results) && rotate.SERVO==1) {
   ak=String(results.value,HEX);
  Serial.println(results.value, HEX);
  Serial.print("ak=");
  Serial.println(ak);
  irrecv.resume(); // Receive the next value
}

    t = rtc.getTime();
  while (ESP_Serial.available() > 0)
     {
     payload = ESP_Serial.readString();
    if(payload.length() > 37){
      current_date=payload.substring(224,226).toInt();
      current_month=payload.substring(228,230).toInt();
      current_year=payload.substring(232,236).toInt();
      current_hour=payload.substring(238,240).toInt();;
      current_minute=payload.substring(242,244).toInt();
      rtc.setTime(current_hour,current_minute, 0);
      rtc.setDate(current_month, current_date, current_year);
      t = rtc.getTime();
     if(t.dow==1){
       th1=payload.substring(0,2).toInt();
       tmin1=payload.substring(4,6).toInt();
       th2=payload.substring(8,10).toInt();
       tmin2=payload.substring(12,14).toInt();
       th3=payload.substring(16,18).toInt();
       tmin3=payload.substring(20,22).toInt();
       th4=payload.substring(24,26).toInt();
       tmin4=payload.substring(28,30).toInt();

     }
     if(t.dow==2){
       th5=payload.substring(32,34).toInt();
       tmin5=payload.substring(36,38).toInt();
       th6=payload.substring(40,42).toInt();
       tmin6=payload.substring(44,46).toInt();
       th7=payload.substring(48,50).toInt();
       tmin7=payload.substring(52,54).toInt();
       th8=payload.substring(56,58).toInt();
       tmin8=payload.substring(60,62).toInt();
       Serial.println(th5);
       Serial.println(tmin5);
       Serial.println(th6);
       Serial.println(tmin6);
       Serial.println(th7);
       Serial.println(tmin7);
       Serial.println(th8);
       Serial.println(tmin8);
     }
     if(t.dow==3){
       th9=payload.substring(64,66).toInt();
       tmin9=payload.substring(68,70).toInt();
       th10=payload.substring(72,74).toInt();
       tmin10=payload.substring(76,78).toInt();
       th11=payload.substring(80,82).toInt();
       tmin11=payload.substring(84,86).toInt();
       th12=payload.substring(88,90).toInt();
       tmin12=payload.substring(92,94).toInt();
     }
     if(t.dow==4){
       th13=payload.substring(96,98).toInt();
       tmin13=payload.substring(100,102).toInt();
       th14=payload.substring(104,106).toInt();
       tmin14=payload.substring(108,110).toInt();
       th15=payload.substring(112,114).toInt();
       tmin15=payload.substring(116,118).toInt();
       th16=payload.substring(120,122).toInt();
       tmin16=payload.substring(124,126).toInt();
     }
      if(t.dow==5){
       th17=payload.substring(128,130).toInt();
       tmin17=payload.substring(132,134).toInt();
       th18=payload.substring(136,138).toInt();
       tmin18=payload.substring(140,142).toInt();
       th19=payload.substring(144,146).toInt();
       tmin19=payload.substring(148,150).toInt();
       th20=payload.substring(152,154).toInt();
       tmin20=payload.substring(156,158).toInt();
     }
     if(t.dow==6){
       th21=payload.substring(160,162).toInt();
       tmin21=payload.substring(164,166).toInt();
       th22=payload.substring(168,170).toInt();
       tmin22=payload.substring(172,174).toInt();
       th23=payload.substring(176,178).toInt();
       tmin23=payload.substring(180,182).toInt();
       th24=payload.substring(184,186).toInt();
       tmin24=payload.substring(188,190).toInt();
     }
     if(t.dow==7){
       //Serial.println(t.hour);
       //Serial.println(t.min);
       th25=payload.substring(192,194).toInt();
       tmin25=payload.substring(196,198).toInt();
       th26=payload.substring(200,202).toInt();
       tmin26=payload.substring(204,206).toInt();
       th27=payload.substring(208,210).toInt();
       tmin27=payload.substring(212,214).toInt();
       th28=payload.substring(216,218).toInt();
       tmin28=payload.substring(220,222).toInt();
      // Serial.println(th25);
       //Serial.println(tmin25);
     }
     flag=1;
}
}
if(flag==1){
  Serial.println(t.hour);
  Serial.print("Min=");
  Serial.println(t.min);
  Serial.println(t.sec);
  delay(1000);
if(t.dow==1 ){
    //Serial.println("DAY=MONDAY");
    count=0;
    if(count==0 && (th1 >0 || tmin1 >0)){
      count=count+1;
      rtc.clearINTStatus();
      rtc.enableInterrupts(th1,tmin1,0);
    }
    if(count==0 && (th1 >0 || tmin1 >0)){
      rotate.step(500);
    }
    if( t.min >= tmin1 && t.hour>=th1 && t.sec> 0 && count==1){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th2,tmin2,0);
  }
  if( t.min >= tmin2 && t.hour >=th2 && t.sec> 0 && count==2){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th3,tmin3,0);
  }
  if( t.min >= tmin3 && t.hour >=th3 && t.sec> 0 && count==3){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th4,tmin4,0);
  }
}
if(t.dow==2 ){
  //Serial.println("DAY=TUESDAY");
  count=0;
  if(count==0 && (th5 >0 || tmin5 >0)){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th5,tmin5,0);
  }
if( t.min >= tmin5 && t.hour >=th5 && t.sec> 0 && count==1){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th6,tmin6,0);
}
if( t.min >= tmin6 && t.hour >=th6 && t.sec> 0 && count==2){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th7,tmin7,0);
}
if( t.min >= tmin7 && t.hour >=th7 && t.sec> 0 && count==3){
  Serial.println("DAY=4");
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th8,tmin8,0);
}
}
if(t.dow==3){
  //Serial.println("DAY=WEDNESDAY");
  count=0;
  if(count==0 && (th9 >0 || tmin9 >0)){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th9,tmin9,0);
  }
if( (t.min >= tmin9 && t.hour >=th9 && t.sec> 0 && count==1) && (th10 >0 || tmin10 >0)){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th10,tmin10,0);
}
if( t.min >= tmin10 && t.hour >=th10 && t.sec> 0 && count==2){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th11,tmin11,0);
}
if( t.min >= tmin11 && t.hour >=th11 && t.sec> 0 && count==3){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th12,tmin12,0);
}
}
if(t.dow==4){
///  Serial.println("DAY=THURSDAY");
  count=0;
  if(count==0 && (th13 >0 || tmin13 >0)){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th13,tmin13,0);
  }
if( t.min >= tmin13 && t.hour >=th13 && t.sec> 0 && count==1){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th14,tmin14,0);
}
if( t.min >= tmin14 && t.hour >=th14 && t.sec> 0 && count==2){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th15,tmin15,0);
}
if( t.min >= tmin15 && t.hour >=th15 && t.sec> 0 && count==3){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th16,tmin16,0);
}
}
if(t.dow==5){
  //Serial.println("DAY=FRIDAY");
  count=0;
  if(count==0 && (th17 >0 || tmin17 >0)){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th17,tmin17,0);
  }
if( t.min >= tmin17 && t.hour >=th17 && t.sec> 0 && count==1){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th18,tmin18,0);
}
if( t.min >= tmin18 && t.hour >=th18 && t.sec> 0 && count==2){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th19,tmin19,0);
}
if( t.min >= tmin19 && t.hour >=th19 && t.sec> 0 && count==3){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th20,tmin20,0);
}
}
if(t.dow==6){
  //Serial.println("DAY=SATURDAY");
    count=0;
  if(count==0 && (th21 >0 || tmin21 >0)){
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th21,tmin21,0);
  }
if( t.min >= tmin21 && t.hour >=th21 && t.sec> 0 && count==1){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th22,tmin22,0);
}
if( t.min >= tmin22 && t.hour >=th22 && t.sec> 0 && count==2){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th23,tmin23,0);
}
if( t.min >= tmin23 && t.hour >=th23 && t.sec> 0 && count==3){
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th24,tmin24,0);
}
}
if(t.dow==7){
  //Serial.println("DAY=SUNDAY");
  count=0;
  if(count==0 && (th25 >0 || tmin25 >0)){
    //Serial.println("1");
    count=count+1;
    rtc.clearINTStatus();
    rtc.enableInterrupts(th25,tmin25,0);
  }
if( t.min >= tmin25 && t.hour >=th25 && t.sec> 0 && count==1){
  //Serial.println("2");
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th26,tmin26,0);
}
if( t.min >= tmin26 && t.hour >=th26 && t.sec> 0 && count==2){
//  Serial.println("3");
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th27,tmin27,0);
}
if( t.min >= tmin27 && t.hour >=th27 && t.sec> 0 && count==3){
  //Serial.println("4");
  count=count+1;
  rtc.clearINTStatus();
  rtc.enableInterrupts(th28,tmin28,0);
}
}
obstacleCheck= digitalRead(obstacle);

    while(rotate.ISR==1){
    Serial.print("Executing ISR");
      rotate.step(-75);
    }
    if(rotate.SERVO==1 && ak=="14ebe01f"){
      if(obstacleCheck==LOW){
        Servo1.write(90);
        delay(1000);
        Servo1.write(0);
        delay(1000);
        rotate.SERVO=0;
        ak=" ";
      }
    }
}
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
