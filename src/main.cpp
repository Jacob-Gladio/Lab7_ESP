//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Global variables
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  Serial.println("Program Started");

  // BMP280 code
  Wire.begin();
 
  if(bmp.begin(Wire.begin())) {
    Serial.println("BMP280 Found");
  }else {
    Serial.println("BMP280 Not Found");
  }
	// LED code
	// Wi-Fi code
	// Routes
	// Server start
}
void loop()
{
}
