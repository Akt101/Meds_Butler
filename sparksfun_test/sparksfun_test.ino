#include <SoftwareSerial.h> // Include software serial library, ESP8266 library dependency
#include <SparkFunESP8266WiFi.h> // Include the ESP8266 AT library
#include <WebSocketClient.h>
const char* ssid     = "cyber_crime";
const char* password = "polyandros";
char path[] = "/";
char host[] = "echo.websocket.org";//demos.kaazing.com
 ESP8266Client client;// Create a client object
WebSocketClient webSocketClient;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DEBUG");
  delay(100);
if (esp8266.begin(115200)) // Initialize the ESP8266 and check it's return status
    Serial.println("ESP8266 ready to go!"); // Communication and setup successful
else
    Serial.println("Unable to communicate with the ESP8266 :(");
int retVal;
//delay(10);
retVal = esp8266.connect("cyber_crime","polyandros");
Serial.print("wifi connection:");Serial.println(retVal);

//delay(100);
if (retVal < 0)
{
    Serial.print(F("Error connecting: "));
    Serial.println(retVal);
}
else{
  Serial.println("wifi connected");
  }
//IPAddress myIP = esp8266.localIP(); // Get the ESP8266's local IP
//Serial.print(F("My IP is: ")); Serial.println(myIP);
//delay(10);
retVal =client.connect("sparkfun.com",80); // Connect to sparkfun (HTTP port)
//delay(5);
Serial.print("client:");
Serial.println(retVal);
if (retVal > 0)
    Serial.println("Successfully connected!");


  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
 int ret= webSocketClient.handshake(client);
 Serial.println(ret);
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
     
  }

}

void loop() {
 // Serial.println(client.available());


}
