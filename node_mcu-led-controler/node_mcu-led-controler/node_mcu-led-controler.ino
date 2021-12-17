#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
MDNSResponder mdns;


const char* ssid = "Galaxy A127724"; // your connection name
const char* password = "ezaz0462"; // your connection password

ESP8266WebServer server(80);
int gpio0_pin = 16; // D0 of nodemcu
int gpio1_pin = 5; // D1 of nodemcu
int gpio2_pin = 4; // D2 of nodemcu
int gpio3_pin = 15; // D8 of nodemcu
int gpio4_pin = 10;  // sd3 of nodemcu
int gpio5_pin = 14; //  D5 of nodemcu
int gpio6_pin = 12;// D6 of nodemcu
int gpio7_pin = 13; // D7 of nodemcu





//Check if header is present and correct
bool is_authentified() {
  Serial.println("Enter is authentified");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == "sina" &&  server.arg("PASSWORD") == "majidi" ) // enter ur username and password you want
    {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      Serial.println("Log in Successful");
      return;

    }

    msg = "Wrong username/password! try again.";
    Serial.println("Log in Failed");
  }
  String content = "<!DOCTYPE html> <html>\n";
  content += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  content += "<title>TESLA Smart Home</title>\n";
  content += "</head>\n";
  content += "<body style='background-color:#fff'><form action='/login' method='POST'><p  align ='center' style='font-size:300%;'><b>  Log In  </b></p><br>";
  content += " <p   align ='center' style='font-size:160%'><b> UserName: <input type='text' name='USERNAME' placeholder='user name' required></b></p><br>";
  content += "<p  align ='center' style='font-size:160%'><b>Password: <input type='password' name='PASSWORD' placeholder='password' required></b></p><br>";
  content += "<p  align ='center' style='font-size:160%'><input style='border: 1px solid red;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;' type='submit' name='submit' value='Log in'></form>" + msg + "</p><br> </body></html>";
  server.send(200, "text/html", content);
}

//root page can be accessed only if authentification is ok
void handleRoot() {
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authentified()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String content =  "<!DOCTYPE html> <html>\n";
  content += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  content += "<title>TESLA Smart Home</title>\n";
  content += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  content += "body{margin-top: 50px;}\n";
  content += ".button {display: inline-block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 0px;cursor: pointer;border-radius: 10px;}\n";
  content += ".button-on {background-color: #1abc9c;}\n";
  content += ".button-on:active {background-color: #16a085;}\n";
  content += ".button-off {background-color: #34495e;}\n";
  content += ".button-off:active {background-color: #2c3e50;}\n";
  content += "p {font-size: 1.2em;color: #000;margin-bottom: 1%;}\n";
  content += ".log_out {border: 1px solid red;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;text-decoration: none;}\n";
  content += ".log_out:hover {background-color:#ff0000;color:#fff}\n";
  content += "</style>\n";
  content += "</head>\n";
  content += "<body>\n";
  content += "<b><u><i><strong>TESLA HOME AUTOMATION</strong></i></u></b></h1><br><p align ='center'>Switch 0 <a class=\"button button-on\" href=\"switch0On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch0Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 1 <a class=\"button button-on\" href=\"switch1On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch1Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 2 <a class=\"button button-on\" href=\"switch2On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch2Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 3 <a class=\"button button-on\" href=\"switch3On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch3Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 4 <a class=\"button button-on\" href=\"switch4On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch4Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 5 <a class=\"button button-on\" href=\"switch5On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch5Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 6 <a class=\"button button-on\" href=\"switch6On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch6Off\">OFF</a></p>";
  content += "<br><p  align ='center'>Switch 7 <a class=\"button button-on\" href=\"switch7On\">ON</a>&nbsp;<a class=\"button button-off\" href=\"switch7Off\">OFF</a></p>";
  content += "</body>\n";
  content += "</html>\n";
  content += "<br><p><marquee direction='right'>Developed by   sina majidi </marquee></p>";
  content += "<br><br><br><br> <footer><p>Posted by: sina majidi</p><p><a href=\"mailto:someone@example.com\">sin.majidi@gmail.com</a>.</p></footer></body>";
  content += "<br><br>You can access this page until you <a class=\"log_out\" href=\"/login?DISCONNECT=YES\">Log Out</a></body></html>";
  server.send(200, "text/html", content);
}

//no need authentification
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}



void setup(void) {


  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio1_pin, OUTPUT);
  digitalWrite(gpio1_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  pinMode(gpio3_pin, OUTPUT);
  digitalWrite(gpio3_pin, LOW);
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, LOW);
  pinMode(gpio5_pin, OUTPUT);
  digitalWrite(gpio5_pin, LOW);
  pinMode(gpio6_pin, OUTPUT);
  digitalWrite(gpio6_pin, LOW);
  pinMode(gpio7_pin, OUTPUT);
  digitalWrite(gpio7_pin, LOW);


  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }


  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works without need of authentification");
  });

  server.onNotFound(handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );


  server.on("/", []() {
    //
  });
  server.on("/switch0On", []() {
    //
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch0Off", []() {
    //
    digitalWrite(gpio0_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch1On", []() {
    //
    digitalWrite(gpio1_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch1Off", []() {
    //
    digitalWrite(gpio1_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch2On", []() {
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch2Off", []() {
    digitalWrite(gpio2_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch3On", []() {
    digitalWrite(gpio3_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch3Off", []() {
    digitalWrite(gpio3_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch4On", []() {
    digitalWrite(gpio4_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch4Off", []() {
    digitalWrite(gpio4_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch5On", []() {
    digitalWrite(gpio5_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch5Off", []() {
    digitalWrite(gpio5_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch6Off", []() {
    digitalWrite(gpio6_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch6On", []() {
    digitalWrite(gpio6_pin, HIGH);
    delay(1000);
    handleRoot();
  });
  server.on("/switch7Off", []() {
    digitalWrite(gpio7_pin, LOW);
    delay(1000);
    handleRoot();
  });
  server.on("/switch7On", []() {
    digitalWrite(gpio7_pin, HIGH);
    delay(1000);
    handleRoot();
  });


  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
