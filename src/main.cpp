//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//Global variables
Adafruit_BME280 bme;
float temperature;

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
	// Wi-Fi code
	// Routes
	// Server start
}
void loop() {
  temperature = bme.readTemperature();
 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
 
  delay(1000);

}
