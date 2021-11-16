#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void setup() {
  Serial.begin(19200);
   WiFiManager wifiManager;
   wifiManager.autoConnect("Medibox");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://mediboard.sumeetgohil.com/api/slots/1");
    int httpCode = http.GET();
    if (httpCode > 0) {
      const size_t bufferSize = JSON_OBJECT_SIZE(54) + 550;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      const char* thr1 = root["thr1"];
      const char* tmin1 = root["tmin1"];
      const char* thr2 = root["thr2"];
      const char* tmin2 = root["tmin2"];
      const char* thr3 = root["thr3"];
      const char* tmin3 = root["tmin3"];
      const char* thr4 = root["thr4"];
      const char* tmin4 = root["tmin4"];
      const char* thr5 = root["thr5"];
      const char* tmin5 = root["tmin5"];
      const char* thr6 = root["thr6"];
      const char* tmin6 = root["tmin6"];
      const char* thr7 = root["thr7"];
      const char* tmin7 = root["tmin7"];
      const char* thr8 = root["thr8"];
      const char* tmin8 = root["tmin8"];
      const char* thr9 = root["thr9"];
      const char* tmin9 = root["tmin9"];
      const char* thr10 = root["thr10"];
      const char* tmin10 = root["tmin10"];
      const char* thr11 = root["thr11"];
      const char* tmin11 = root["tmin11"];
      const char* thr12 = root["thr12"];
      const char* tmin12 = root["tmin12"];
      const char* thr13 = root["thr13"];
      const char* tmin13 = root["tmin13"];
      const char* thr14 = root["thr14"];
      const char* tmin14 = root["tmin14"];
      const char* thr15 = root["thr15"];
      const char* tmin15 = root["tmin15"];
      const char* thr16 = root["thr16"];
      const char* tmin16 = root["tmin16"];
      const char* thr17 = root["thr17"];
      const char* tmin17 = root["tmin17"];
      const char* thr18 = root["thr18"];
      const char* tmin18 = root["tmin18"];
      const char* thr19 = root["thr19"];
      const char* tmin19 = root["tmin19"];
      const char* thr20 = root["thr20"];
      const char* tmin20 = root["tmin20"];
      const char* thr21 = root["thr21"];
      const char* tmin21 = root["tmin21"];
      const char* thr22 = root["thr22"];
      const char* tmin22 = root["tmin22"];
      const char* thr23 = root["thr23"];
      const char* tmin23 = root["tmin23"];
      const char* thr24 = root["thr24"];
      const char* tmin24 = root["tmin24"];
      const char* thr25 = root["thr25"];
      const char* tmin25 = root["tmin25"];
      const char* thr26 = root["thr26"];
      const char* tmin26 = root["tmin26"];
      const char* thr27 = root["thr27"];
      const char* tmin27 = root["tmin27"];
      const char* thr28 = root["thr28"];
      const char* tmin28 = root["tmin28"];
      const char* current_date= root["current_date_day"];
      const char* current_month=root["current_date_month"];
      const char* current_year=root["current_date_year"];
      const char* current_hour=root["current_time_hr"];
      const char* current_minute=root["current_time_min"];
      Serial.println(thr1);
      delay(100);
      Serial.println(tmin1);
      delay(100);
      Serial.println(thr2);
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
      delay(100);
      Serial.println(thr28);
      delay(100);
      Serial.println(tmin28);
      delay(100);
      Serial.println(current_date);
      delay(100);
      Serial.println(current_month);
      delay(100);
      Serial.println(current_year);
      delay(100);
      Serial.println(current_hour);
      delay(100);
      Serial.println(current_minute);
      delay(100);
    }
    http.end();
  }
  delay(1980000);
}