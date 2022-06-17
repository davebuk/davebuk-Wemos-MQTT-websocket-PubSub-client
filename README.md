﻿## Wemos-MQTT-websocket-PubSub-client
 
 This project came about while looking for a quick way of seeing the status of various espurna flashed IOT devices. All of my devices use the MQTT protocal to communicate with openHAB.
 
 Using the option of MQTT over websockets, I found a web based MQTT client made by HiveMQ that will run in a single web page. I wondered if it was possible to run the page in a web server hosted on an ESP8266 WEMOS D1 MINI board.
 
 After some testing I was able to get the web server running using ESPAsyncWebServer and LittleFS to hold the web page and java script files.
 
 The code can be built using platformIO, flashed to a WEMOS D1 MINI and the file system held in the `/data` directory uploaded.
 
 ## Wifi connection
 
 Currently you need to change the Wifi SSID and password in the '/src/main.cpp' file before building and flashing. I plan to add a captive Wifi portal so this isn't needed.
 
 ## MQTT Broker and websockets
