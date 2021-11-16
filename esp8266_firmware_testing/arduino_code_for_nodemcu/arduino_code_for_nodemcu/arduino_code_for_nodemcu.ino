#include <SoftwareSerial.h>
String payload;
SoftwareSerial ESP_Serial(6, 7); //Tx,Rx


void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 ESP_Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (ESP_Serial.available() > 0)
    {
    payload = ESP_Serial.readString();
    Serial.println(payload);
    delay(500);
    }
    
}
