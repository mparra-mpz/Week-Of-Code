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

unsigned long iter = 0;
unsigned long error = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11_VERSION);
  Serial.println();
}

void loop() {
  DHT11 sensor = DHT11(DHT11_PIN);
  DHT11_STATE state;
  
  state = sensor.read();
  
  switch (state) {
    case OK:  
      Serial.print("OK");
      break;
    case ERROR_CHECKSUM:
      Serial.print("Checksum ERROR");
      break;
    case ERROR_CONNECTION_L:
      Serial.print("Connection ERROR LOW signal");
      break;
    case ERROR_CONNECTION_H:
      Serial.print("Connection ERROR HIGH signal");
      break;
    case ERROR_ACK_L:
      Serial.print("ACK ERROR LOW signal");
      break;
    case ERROR_ACK_H:
      Serial.print("ACK ERROR HIG signal");
      break;
    default:
      Serial.print("Unknown ERROR");
      break;
  }

  if (state == OK) {
    iter++;
  } else {
    error++;
  }
  
  float humidity = sensor.getHumidity();
  float temperature = sensor.getTemperature();
  Serial.print(" Humidity (%): ");
  Serial.print(humidity);
  Serial.print(" Temperature (°C): ");
  Serial.print(temperature);
  Serial.print(" Iteration: ");
  Serial.print(iter);
  Serial.print(" Error: ");
  Serial.print(error);
  Serial.print("\n");
  
  delay(10000);
}
