#include "Main.h"
#define DEBUG

void setup(){
  //setup rtc
  //motor
  //esp8266

}

void loop(){
  //despense medicine depends upon rtc
  #ifdef DEBUG
    Serial.begin(115200);
    delay(10);
    Serial.println("MediBox is Ready")
  #endif

}

void Isr_Int(){

}
