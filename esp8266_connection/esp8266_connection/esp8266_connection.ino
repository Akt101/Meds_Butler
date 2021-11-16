
//This code is Written by Abhinav verma.
//contact @ abhikumar134@gmail.com
//This software is only for education purpose for Students, hobbyist.
// don't use for commercial.
// here we are controlling on board led using web api integration of 
// thingspeak.com using internet.
//
//
#include <SoftwareSerial.h>
#include <WebSocketClient.h>
#include<WiFi.h>
// change esp8266 default bude rate to 57600 bps before loading this software
// LED 
#define DEBUG true
int ledPin = 13;
// replace with your channel's thingspeak API key
//String apiKey = "your api key";
String ssid="cyber_crime";
String pswd="polyandros";
String wifi;
// connect 10 to TX of Serial USB
// connect 11 to RX of serial USB
SoftwareSerial ser(3, 2); // RX, TX using software serial for esp8266
char path[] = "/";
char host[] = "echo.websocket.org";
WebSocketClient webSocketClient;
// Use WiFiClient class to create TCP connections
WiFiClient client;

// this runs once
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);    

  // enable debug serial
  Serial.begin(9600);
  // enable software serial
  ser.begin(115200);
  Serial.println("DEBUG");
  String getStr = "GET /channels/your channel/fields/1.json?results=1";
  getStr += "\r\n";
  Serial.println(getStr.length());
  sendData( "AT",1000,DEBUG);
  delay(1000);
  sendData("AT+CWJAP_DEF=\""+ssid+"\",\""+pswd+"\"",5000,DEBUG);
  delay(6000);
  //sendData("AT+CIFSR",5000,DEBUG);
  //delay(2000);
  sendData("AT+CIPSTART=\"TCP\",\"sails-arduino.herokuapp.com\",\"80\"",5000,DEBUG);

  //Serial.println(client);
    webSocketClient.path = path;
  webSocketClient.host = host;
 /* if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }*/
}


// the loop 
void loop() {
   
}
void sendData(String command, const int timeout, boolean debug){
    String response = "";    
    ser.println(command); 
    //Serial.println(command);
   delay(5);
    if(debug){
    long int time = millis();   
    while( (time+timeout) > millis()){
      while(ser.available()){       
        response += char(ser.read());
      }  
    }    
      Serial.print(response);
    }    
}
