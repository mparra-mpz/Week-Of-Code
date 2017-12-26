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
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop() {
  DHT11 sensor = DHT11(DHT11_PIN);
  DHT11_STATE state;
  
  state = sensor.read();
  
  switch (state) {
    case OK:  
      Serial.print("OK,\t");
      break;
    case ERROR_CHECKSUM:
      Serial.println("Checksum ERROR");
      break;
    case ERROR_CONNECTION_L:
      Serial.println("Connection ERROR LOW signal");
      break;
    case ERROR_CONNECTION_H:
      Serial.println("Connection ERROR HIGH signal");
      break;
    case ERROR_ACK_L:
      Serial.println("ACK ERROR LOW signal");
      break;
    case ERROR_ACK_H:
      Serial.println("ACK ERROR HIG signal");
      break;
    default:
      Serial.println("Unknown ERROR");
      break;
  }

  if (state == OK) {
    float humidity = sensor.getHumidity();
    float temperature = sensor.getTemperature();
    Serial.print("DHT11, \t");
    Serial.print(humidity);
    Serial.print(",\t");
    Serial.println(temperature);
  }
  
  delay(10000);
}
