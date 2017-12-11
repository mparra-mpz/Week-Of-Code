/*
 * Author: Manuel Parra Z.
 * Date: 10/12/2017
 * License: MIT License
 * Hardware:
 *      - Arduino Uno R3
 *      - TMP36GZ Sensor.
 * Description: Project to Measure ambient temperature using an Arduino Uno R3
 * and a TMP36GZ sensor. 
 * Link: https://github.com/mparra-mpz/week-of-code/wiki/Week-3:-Raspberry-Room-Temperatures
 */

const int sensorPin = A0;
const int sample = 100;
const int pause = 10 * 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue;
  float temperature;
  float voltage;
  float store = 0;
  
  // Read the temperature 10 times and report the average value.
  for(int i=0; i<sample; i++) {
    sensorValue = analogRead(sensorPin);
    voltage = (sensorValue / 1024.0) * 5.0;
    temperature = (voltage - 0.5) * 100.0;
    store = store + temperature;
  }
  
  temperature = store / sample;
  Serial.println(temperature);
  delay(pause);
}
