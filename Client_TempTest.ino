// Setup the client to send sensor data to the server
#include <ESP8266WiFi.h>

// Initialize sensor parameters
int temp = 101;
// Initialize network parameters
const char* ssid = "Tazer Tag";
const char* password = "TazerTag";
const char* host = "192.168.11.4"; // as specified in server.ino

// Set up the client objet
WiFiClient client;


void setup() {
  // Connect to the server
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("IP Address (AP): "); Serial.println(WiFi.localIP());
  
  Serial.print("Temp : "); Serial.println(temp);
  
  // Connect to the server and send the data as a URL parameter
  if(client.connect(host,80)) {
    String url = "/update?value=";
    url += String(temp);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host +  "\r\n" + 
                 "Connection: keep-alive\r\n\r\n"); // minimum set of required URL headers
                 Serial.println(String(temp));
    delay(10);
    // Read all the lines of the response and print them to Serial
    Serial.println("Response: ");
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
 
}

void loop() {
  // put your main code here, to run repeatedly:
}
