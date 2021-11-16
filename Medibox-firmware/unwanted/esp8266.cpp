#include "Arduino.h"
#include "esp8266.h"
#include <SoftwareSerial.h>
#define DEBUG true
Esp8266::Esp8266(int RX,int TX):mySerial(SoftwareSerial(RX,TX)){

  _rx=RX;
  _tx=TX;
//  SoftwareSerial mySerial=SoftwareSerial(_rx,_tx);
  mySerial.begin(115200);
}
void Esp8266::sendData(String command, const int timeout, boolean debug){
    String response = "";
    mySerial.println(command);
    Serial.println(command);
   delay(5);
   if(debug){
     //Serial.println("inside debug if");
    long int time = millis();
    while( (time+timeout) > millis()){
      while(mySerial.available()){
        response += char(mySerial.read());

      }
    }
      Serial.println(response);
    }

}

void Esp8266::WiFiConnect(String ssid,String pswd){
 Serial.println("DEBUG");
 sendData("AT",1000,DEBUG);
 //delay(1000);
 sendData("AT+CWJAP_DEF=\""+ssid+"\",\""+pswd+"\"",3000,DEBUG);
 //delay(1000);
 sendData("AT+CIFSR",1000,DEBUG);
 sendData("AT+CIPSTART=\"TCP\",\"192.168.0.102\",\"747\"",1000,DEBUG);
}
