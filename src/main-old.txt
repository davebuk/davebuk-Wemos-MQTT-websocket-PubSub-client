// Import required libraries
#include <FS.h>
#include <LittleFS.h>
 
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
// Replace with your network credentials
const char* ssid = "ssid"; //Replace with your own SSID
const char* password = "ssidpw"; //Replace with your own password

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

 
void setup(){

  Serial.begin(115200);

  // Initialize LittleFS
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
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

  // Start server
  server.begin();
}
 
void loop(){
  
}
