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
 
#include <DHT11.h>
#define DHT11_PIN 4

void setup() {
  Serial.begin(9600);
  // Basic information.
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop() {
  DHT11 sensor = DHT11(DHT11_PIN);
  DHT11_STATE state;
  
  Serial.print("DHT11, \t");
  state = sensor.read();
  
  // Check if data is valid.
  switch (state) {
    case OK:  
      Serial.print("OK,\t");
      break;
    case ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }
  
  // Display data.
  float humidity = sensor.getHumidity();
  float temperature = sensor.getTemperature();
  Serial.print(humidity);
  Serial.print(",\t");
  Serial.println(temperature);
  delay(5000);
}
