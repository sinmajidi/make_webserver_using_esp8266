#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 
 
/* Set these to your desired credentials. */ 
const char *ssid = "Galaxy A127724"; //Enter your WIFI ssid 
const char *password = "ezaz0462"; //Enter your WIFI password 

ESP8266WebServer server(80); 
String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: inline-block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>sina majidi Relay control</h1>\n";
  ptr +="<h3>cybele.ir</h3>\n";
  {ptr +="<p>LED Status: ON</p><a class=\"button button-off\" href=\"/LED_BUILTIN_off\">OFF</a>\n";}
  {ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/LED_BUILTIN_on\">ON</a>\n";}
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
} 
 
void handleRoot() { 
  server.send(200,  "text/html", SendHTML()); 
} 
void handleSave() { 
  if (server.arg("pass") != "") { 
    Serial.println(server.arg("pass")); 
  } 
} 

void setup() { 
  pinMode(LED_BUILTIN, OUTPUT); 
  delay(3000); 
  Serial.begin(115200); 
  Serial.println(); 
  Serial.print("Configuring access point..."); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP()); 
  server.on ( "/", handleRoot ); 
  server.on ("/save", handleSave); 
  server.begin(); 
  Serial.println ( "HTTP server started" ); 
  server.on("/LED_BUILTIN_on", []() { 
    digitalWrite(LED_BUILTIN, 1); 
    Serial.println("on"); 
    handleRoot(); 
  }); 
  server.on("/LED_BUILTIN_off", []() { 
    digitalWrite(LED_BUILTIN, 0); 
    Serial.println("off"); 
    handleRoot(); 
  }); 
} 
 
void loop() { 
  server.handleClient(); 
}
