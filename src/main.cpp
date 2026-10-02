//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <WebServer.h>

//Global variables
Adafruit_BME280 bme;
float temperature;
const char* ssid = "JacobWiFi";
const char* password = "Donttell";
const int ledPin = 23;

//Web server & page
WebServer server(80);
const char webpage[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<meta http-equiv="refresh" content="5">

<title>ESP32 Environmental Monitor</title>

<style>

body{
    font-family:Arial,sans-serif;
    background:linear-gradient(
        135deg,
        #1E3C72,
        #2A5298
    );
    color:white;
    text-align:center;
    margin:0;
    padding:20px;
}

.container{
    max-width:800px;
    margin:auto;
}

.card{
    background:rgba(
        255,
        255,
        255,
        0.15
    );

    padding:25px;
    border-radius:15px;

    box-shadow:
    0px 4px 12px rgba(
        0,
        0,
        0,
        0.3
    );
}

.value{
    font-size:42px;
    font-weight:bold;
    color:#FFD54F;
}

button{

    width:180px;
    height:60px;

    margin:10px;

    font-size:20px;

    border:none;

    border-radius:10px;

    cursor:pointer;
}

.on{
    background:#4CAF50;
    color:white;
}

.off{
    background:#F44336;
    color:white;
}

.info{
    margin-top:20px;
}

</style>

</head>

<body>

<div class="container">

<h1>🌎 ESP32 Environmental Monitor</h1>

<div class="card">

<h2>Temperature</h2>

<p class="value">
TEMP_PLACEHOLDER
</p>

</div>

<br>

<button class="on"
onclick="location.href='/on'">
LED ON
</button>

<button class="off"
onclick="location.href='/off'">
LED OFF
</button>

<div class="info">

<p>
SSID: ESP32_Lab7
</p>

<p>
IP Address: 192.168.4.1
</p>

</div>

</div>

</body>

</html>

)rawliteral";

//Webpage temperature
void handleRoot() {
  String page = webpage;

  //Read temperature
  temperature = bme.readTemperature();
 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
 
  delay(1000);

  //Send data to webpage
  page.replace( "TEMP_PLACEHOLDER", String (temperature, 1) + "°C" );
  server.send( 200, "text/html", page );
}

//Webpage LED
void handleLEDOn() {
  Serial.println("LED ON Route Accessed");
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}
void handleLEDOff() {
  Serial.println("LED OFF Route Accessed");
	digitalWrite( ledPin, LOW);
	server.sendHeader("Location", "/" );
	server.send(303);

}

void setup() {
  Serial.begin(115200);
  Serial.println("Program Started");

  // BMP280 code
  Wire.begin();
  
  if(bme.begin(0x76)) {
    Serial.println("BME280 Found");
  }else {
    Serial.println("BME280 Not Found");
  }
	// LED code
  pinMode(ledPin, OUTPUT);

	// Wi-Fi code
  WiFi.softAP(ssid, password);
  Serial.print("IP Address: ");
 
  Serial.println(WiFi.softAPIP());

	// Routes
  server.on( "/", handleRoot );

  server.on("/on", handleLEDOn);

  server.on("/off", handleLEDOff);


	// Server start
  server.begin();
  Serial.println("Web Server Started");

}
void loop() {
  server.handleClient();
}
