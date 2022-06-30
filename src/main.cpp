#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"

AsyncWebServer server(80);

const char* input_parameter1 = "ssid";
const char* input_parameter2 = "pass";
const char* input_parameter3 = "ip";

//Variables to save values from HTML form
String ssid;
String pass;
String ip;

// File paths to save input values permanently
const char* SSID_path = "/ssid.txt";
const char* Password_path = "/pass.txt";
const char* IP_path = "/ip.txt";

boolean restart = false;

IPAddress localIP;
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

unsigned long previous_time = 0;
const long Delay = 10000; 


// Read File from LittleFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path,"r");
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  file.close();
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path,"w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

// Initialize WiFi
bool initialize_Wifi() {
  if(ssid=="" || ip==""){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());

  if (!WiFi.config(localIP, gateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");
  delay(20000);
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect.");
    return false;
  }

  Serial.println(WiFi.localIP());
  return true;
}

void setup() {
  Serial.begin(115200);

  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else{
   Serial.println("LittleFS mounted successfully");
  }

  ssid = readFile(LittleFS, SSID_path);
  pass = readFile(LittleFS, Password_path);
  ip = readFile(LittleFS, IP_path);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);

  // Load HiveMQTT web page
  if(initialize_Wifi()) {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(LittleFS, "/index.html", "text/html");
    });
    
    server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/css/style.css", "text/css");
  });
  
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/favicon.ico", "image/x-icon");
  });
  
  server.on("/css/jquery.minicolors.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/css/jquery.minicolors.css", "text/css");
  });
  
  server.on("/css/normalize.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/css/normalize.css", "text/css");
  });
  
  server.on("/css/foundation.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/css/foundation.css", "text/css");
  });

  server.on("/config.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/config.js", "text/javascript");
  });

  server.on("/js/app.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/app.js", "text/javascript");
  });
  server.on("/js/custom-combobox.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/custom-combobox.js", "text/javascript");
  });
  
 server.on("/js/encoder.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/encoder.js", "text/javascript");
  });
  
 server.on("/js/jquery.minicolors.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/jquery.minicolors.min.js", "text/javascript");
  });
  server.on("/js/mqttws31.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/mqttws31.js", "text/javascript");
  });
 
  server.on("/js/arrow.gif", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/arrow.gif", "image/gif");
  });
 
    server.on("/js/cross.gif", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/cross.gif", "image/gif");
  });
 
  server.on("/js/hs.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/hs.png", "image/png");
  });

  server.on("/js/hv.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/js/hv.png", "image/png");
  });

  server.on("/assets/arrow_down.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/arrow_down.png", "image/png");
  });

 server.on("/assets/arrow_up.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/arrow_up.png", "image/png");
  });

  server.on("/assets/chevron-double-3-01.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/chevron-double-3-01.png", "image/png");
  });

  server.on("/assets/chevron-double-3-02.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/chevron-double-3-02.png", "image/png");
  });

  server.on("/assets/chevron-double-3-02.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/chevron-double-3-02.png", "image/png");
  });

  server.on("/assets/jquery.minicolors.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/jquery.minicolors.png", "image/png");
  });

  server.on("/assets/hivemq-logo.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/assets/hivemq-logo.svg", "image/svg+xml");
  });
    
    server.serveStatic("/", LittleFS, "/");
    
    server.begin();
  }
  else {
    Serial.println("Setting Access Point");
    WiFi.softAP("ESP8266-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", LittleFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == input_parameter1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(LittleFS, SSID_path, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == input_parameter2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(LittleFS, Password_path, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == input_parameter3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(LittleFS, IP_path, ip.c_str());
          }
        }
      }
      restart = true;
      request->send(200, "text/plain", "Success. ESP8266 will now restart. Connect to your router and go to IP address: " + ip);
    });
    server.begin();
  }
}

void loop() {
   if (restart){
    delay(5000);
    ESP.restart();
  }


}
