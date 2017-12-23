/*
 * Author: Manuel Parra Z.
 * Date: 23/12/2017
 * License: MIT License
 * Hardware:
 *      - Arduino Uno R3
 *      - DHT11 DFRobot Sensor.
 * Description: Project to Measure ambient temperature and humidity using an Arduino Uno R3
 * and a  DHT11 DFRobot Sensor.
 * Link: https://github.com/mparra-mpz/week-of-code/wiki/Week-4:-Raspberry-Weather-Station
 */
 
#include <dht11.h>
#define DHT11_PIN 4

void setup() {
  Serial.begin(9600);
  // Basic information.
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop() {
  dht11 sensor;
  int chk;
  
  Serial.print("DHT11, \t");
  // Read the data.
  chk = sensor.read(DHT11_PIN);
  
  // Check if data is valid.
  switch (chk) {
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
  
 // Display data.
  Serial.print(sensor.humidity);
  Serial.print(",\t");
  Serial.println(sensor.temperature);
  delay(2000);
}

