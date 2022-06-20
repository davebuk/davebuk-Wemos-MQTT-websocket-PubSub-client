## Wemos-MQTT-websocket-PubSub-client
 
 This project came about while looking for a quick way of seeing the status of various espurna flashed IOT devices. All of my devices use the MQTT protocol to communicate with openHAB. The project is my first attempt at bringing code like this together so there maybe a chance things will stop working. Feel free to offer any Pull requests or raise issues, but I can't promise to be able to implement ideas or fix things quickly. :)
 
 Using the option of MQTT over websockets, I found a web based MQTT client made by HiveMQ that will run in a single web page. I wondered if it was possible to run the page in a web server hosted on an ESP8266 WEMOS D1 MINI board.
 
 After some testing I was able to get the web server running using ESPAsyncWebServer and LittleFS to hold the web page and java script files.
 
 The code can be built using platformIO, flashed to a WEMOS D1 MINI and the file system held in the `/data` directory uploaded.
 
 ## Wifi connection
 
 Currently you need to change the Wifi SSID and password in the '/src/main.cpp' file before building and flashing. I plan to add a captive Wifi portal so this isn't needed.
 
 ## MQTT Broker and websockets

For this project to work, your MQTT broker needs to support websockets and have the port enabled. I use openhabian to run openHAB and the built in mosquitto broker. You need to edit the broker config. to allow websocket connections. From an SSH connection to openhabian run 'sudo nano /etc/mosquitto/mosquitto.conf' 

Add the following to allow websockets on the port you require. I believe you need to define the tcp port here as well even though its already been working.
```
# this will listen for mqtt on tcp
listener 1883
# this will expect websockets connections e.g. 9000
listener 9000
protocol websockets
```

Save then restart mosquitto using `sudo /etc/init.d/mosquitto restart`. 

## MQTT Examples based on espurna MQTT messages

With a devices {root} e.g. `Device001`, to view all messages for that topic, subscribe to `Device001/#`.
To force a heartbeat update for that device, publish to the topic `Device001/action/set` with a message of `heartbeat`.
To toggle the relay #0 for that device, publish to the topic `Device001/relay/0/set` with a message of `2`