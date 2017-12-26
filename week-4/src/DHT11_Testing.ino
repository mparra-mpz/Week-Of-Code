/*
 * Author: Manuel Parra Z.
 * Date: 23/12/2017
 * License: MIT License
 * Hardware:
 *      - Arduino One R3
 *      - DHT11 DFRobot Sensor.
 * Description: C++ library draft for DHT11 DFRobot Sensor.
 */

#define pause 10000 // 10 seconds.
int dataPin = 4;
int timeout = 100;

void setup() {
  Serial.begin(9600);
  Serial.println("     DHT11   TESTING     ");
  Serial.println("=========================");
}

void loop() {
  unsigned long ini;
  unsigned long fin;
  
  // Buffer to receive data.
  uint8_t bits[5];
  uint8_t pos = 7;
  uint8_t idx = 0;
  unsigned long timeStore[40];
  
  // Empty buffer.
  for (int i=0; i< 5; i++) {
    bits[i] = 0;
  }
  
  /*
   * MCU START SIGNAL
   * The MCU pull down the voltage in the digital pin for at least 18[ms] to
   * let DHT11 detect the signal. Pull up the digital pin and wait between
   * 20[us] to 40[us] for DHT11 response.
   */
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW);
  delay(20);
  digitalWrite(dataPin, HIGH);
  pinMode(dataPin, INPUT);
  delayMicroseconds(40);

  /*
   * DHT11 RESPONSE SIGNAL
   * The DHT11 send a low voltage level signal to the digital pin which lasts
   * 80[us], then send a high voltage level signal to the digital pin and keeps
   * during 80[us] meanwhile DHT11 is preparing to send the data.
   */
  // Low voltage signal detection.
  ini = micros();
  while (digitalRead(dataPin) == LOW) {
    fin = micros();
    if ((fin-ini) > timeout) {
      Serial.println("=========================");
      Serial.println("TIMEOUT, go to next cycle");
      Serial.println("=========================");
    }
  }
  // High voltage signal detection.
  ini = micros();
  while (digitalRead(dataPin) == HIGH) {
    fin = micros();
    if ((fin-ini) > timeout) {
      Serial.println("=========================");
      Serial.println("TIMEOUT, go to next cycle");
      Serial.println("=========================");
    }
  }
  
  /*
   * DHT11 DATA
   * Before send a bit the DHT11 send a low voltage level signal during 
   * 50[us], then it send a high voltage level signal, if the high voltage
   * level signal took between 26[us] to 28[us] the bit is 0, if the high
   * voltage level signal took 70[us] the bit is 1.
   *
   * DHT11 sends 40 bits of data: 8 bits for integral humidity, 8 bits for
   * decimal humidity, 8 bits for integral temperature, 8 bits for decimal
   * temperature and finally 8 bits for parity check.
   */
  for (int i=0; i<40; i++) {
    // Low voltage level signal detection.
    ini = micros();
    while (digitalRead(dataPin) == LOW) {
      fin = micros();
      if ((fin-ini) > timeout) {
        Serial.println("=========================");
        Serial.println("TIMEOUT, go to next cycle");
        Serial.println("=========================");
      }
    }
    
    // Mesure high voltage level signal duration.
    ini = micros();
    while (digitalRead(dataPin) == HIGH) {
      fin = micros();
      if ((fin-ini) > timeout) {
        Serial.println("=========================");
        Serial.println("TIMEOUT, go to next cycle");
        Serial.println("=========================");
      }
    }
    
    // If high voltage level signal take more than 50[us] change the bit in pos to 1.
    if ((fin-ini) > 50) {
      bits[idx] |= (1 << pos);
    }
    timeStore[i] = fin - ini;
    
    // If pos is 0, go to the next byte starting in the MSB. 
    if (pos == 0) {
      pos = 7;
      idx++;
    } else {
      pos --;
    }
    
  }

  // Print the time array for the study.
  pos = 8;
  idx = 0;
  for (int j=0; j<40; j++) {
    Serial.print(timeStore[j]);
    Serial.print(" | ");
    pos--;
    if (pos == 0) {
      Serial.print(" ---> ");
      Serial.print(bits[idx]);
      Serial.print("\n");
      idx++;
      pos = 8;
    }
  }

  Serial.println("=========================");
  delay(pause);
}
