#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "SSID HERE";
const char* password = "PASSWORD HERE";
char path[] = "/";
char host[] = "echo.websocket.org";
  
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
ESP8266Client client;

void setup() {
 Serial.begin(9600);
 Serial.println(esp8266.begin());
 if (esp8266.begin()) // Initialize the ESP8266 and check it's return status
    Serial.println("ESP8266 ready to go!"); // Communication and setup successful
else
    Serial.println("Unable to communicate with the ESP8266 :(");
int retVal;
retVal = esp8266.connect(ssid, password);
if (retVal < 0)
{
    Serial.print(F("Error connecting: "));
    Serial.println(retVal);
}
IPAddress myIP = esp8266.localIP(); // Get the ESP8266's local IP
Serial.print(F("My IP is: ")); Serial.println(myIP);

retVal = client.connect("sparkfun.com", 80); // Connect to sparkfun (HTTP port)
if (retVal > 0)
    Serial.println("Successfully connected!");
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }
  }




void loop() {
  String data;

  if (client.connected()) {
    
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
    
    // capture the value of analog 1, send it along
    pinMode(1, INPUT);
    data = String(analogRead(1));
    
    webSocketClient.sendData(data);
    
  } else {
    Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
    }
  }
  
  // wait to fully let the client disconnect
  delay(3000);
  
}
