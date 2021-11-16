#ifndef Esp8266_h
#define Esp8266_h

#include "Arduino.h"
#include "pins.h"
#include <SoftwareSerial.h>

class Esp8266
{
  public:
    Esp8266(int RX,int TX);
    void sendData(String command, const int timeout, boolean debug);
    void WiFiConnect(String ssid, String pswd);
  private:
    SoftwareSerial mySerial;
    int _rx,_tx;

};

#endif
