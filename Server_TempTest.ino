 
// Setup the server to receive data over WiFi
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configuration parameters for Access Point
char * ssid_ap = "Tazer Tag";
char * password_ap = "TazerTag";
IPAddress ip(192,168,11,4); // arbitrary IP address (doesn't conflict w/ local network)
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);

// Set up the server object
ESP8266WebServer server;

// Keep track of the sensor data that's going to be sent by the client

String tmpString = "";
unsigned int temp = 0;
int tag = 0;

//Set HTML
//HTML
String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
 <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
 <meta charset='utf-8'>
 <meta http-equiv='refresh' content='5'>
 <style>
   body {font-size:110%;} 
   #main {display: table; margin: auto;  padding: 0 12px 0 12px; } 
   #temp {display:table; margin auto; padding: 0 8px 0 8px; }
   h2 {text-align:center; } 
   p { text-align:center; }
 </style>
   <title>Tazer Tag Score Board</title>
 </head>
 
 <body>
   <div id='main'>
     <h2>Tazer Tag Score</h2>
     <div id='temp'> 
       <p>Temp = %temp%</p>
     </div>
   </div> 
 </body>
</html>
)=====";
void setup() {

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(ssid_ap,password_ap);
  // Print IP Address as a sanity check
  Serial.begin(115200);
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  
  
  
  // Configure the server's routes
  server.on("/",handleIndex); // use the top root path to report the last sensor value
  server.on("/update",handleUpdate); // use this route to update the sensor value
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
//tmpString = html_1;
    html_1.replace("%temp%", String(temp));
    html_1.replace("%tag%", String(tag) );
    //Serial.println(String(temp));
   temp = String(temp).toFloat();
    Serial.print("Tag = ");Serial.println(tag);
delay(1000);
   Serial.print("Temp = "); Serial.println(temp);
}

void handleIndex() {
  server.send(200,"text/html", html_1); // we'll need to refresh the page for getting the latest value
  
}

void handleUpdate() {
  // The value will be passed as a URL argument
  temp = server.arg("value").toFloat();
  //Serial.println(temp);
  //server.send(200,"text/plain","Updated");
}
