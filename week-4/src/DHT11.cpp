/*
 * Author: Manuel Parra Z.
 * Date: 27/12/2017
 * License: MIT License
 * Hardware:
 *      - Raspberry Pi B+.
 *      - DHT11 DFRobot Sensor.
 * Description: C++ library for DHT11 DFRobot Sensor.
 */
#include "DHT11.h"
#include <chrono>
#include <time.h>
#include <wiringPi.h>

DHT11::DHT11(int _pin) {
    this->pin = _pin;
    this->humidity = -1.0;
    this->temperature = -1.0;
    this->realTime = false;
    // The timeout for the signal detection is 100[us].
    this->timeout = 100;

    // Initialize wiring pi.
    wiringPiSetup();
    
    // Set the maximum priority to the program.
    int priority = piHiPri(99);
    // Check if real time status.
    this->realTime = ((priority == 0) ? true : false);
}

DHT11_STATE DHT11::read() {
    //Measure elapsed time.
    auto ini;
    auto fin;
    // Time structure.
    struct timespec wait;

    // Bit handling.
    uint8_t pos = 7;
    uint8_t idx = 0;

    // Buffer to 0.
    for (int i=0; i< 5; i++) {
        this->bits[i] = 0;
    }

    /*
     * MCU START SIGNAL
     * The MCU pull down the voltage in the digital pin for at least 18[ms] to
     * let DHT11 detect the signal. Pull up the digital pin and wait between
     * 20[us] to 40[us] for DHT11 response.
     */
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);

    // Pause during 20[ms].
    wait.tv_sec = 0;
    wait.tv_nsec = 20 * 1000000L;
    nanosleep(&wait, (struct timespec *)NULL);

    digitalWrite(this->pin, HIGH);
    pinMode(this->pin, INPUT);

    // Pause during 40[us].
    wait.tv_sec = 0;
    wait.tv_nsec = 40 * 1000L;
    nanosleep(&wait, (struct timespec *)NULL);
    
    /*
     * DHT11 RESPONSE SIGNAL
     * The DHT11 send a low voltage level signal to the digital pin which lasts
     * 80[us], then send a high voltage level signal to the digital pin and
     * keeps during 80[us] meanwhile DHT11is preparing to send the data.
     */
    // Low voltage signal detection.
    ini = std::chrono::high_resolution_clock::now();
    while (digitalRead(this->pin) == LOW) {
        fin = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::microseconds>(fin-ini).count() > this->timeout) {
            return ERROR_CONNECTION_L;
        }
    }

    // High voltage signal detection.
    ini = std::chrono::high_resolution_clock::now();
    while (digitalRead(this->pin) == HIGH) {
        fin = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::microseconds>(fin-ini).count() > this->timeout) {
            return ERROR_CONNECTION_H;
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
     * temperature and finally 8 bits for a checksum verification.
     */
    for (int i=0; i<40; i++) {
        // Low voltage signal detection.
        ini = std::chrono::high_resolution_clock::now();
        while (digitalRead(this->pin) == LOW) {
            fin = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::microseconds>(fin-ini).count() > this->timeout) {
                return ERROR_ACK_L;
            }
        }

        // Mesure high voltage signal duration.
        ini = std::chrono::high_resolution_clock::now();
        while (digitalRead(this->pin) == HIGH) {
            fin = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::microseconds>(fin-ini).count() > this->timeout) {
                return ERROR_ACK_H;
            }
        }

        // If high voltage level signal take more than 50[us], the bit is 1.
        if (std::chrono::duration_cast<std::chrono::microseconds>(fin-ini).count() > 50) {
            this->bits[idx] |= (1 << pos);
        }

        // If the pos is 0, go to the next byte starting in the MSB. 
        if (pos == 0) {
            pos = 7;
            idx++;
        } else {
            pos--;
        }
    }
    
    // Perform a checksum verification.
    uint8_t checksum = this->bits[0] + this->bits[1] + this->bits[2] + this->bits[3];
    if (this->bits[4] != checksum) {
        return ERROR_CHECKSUM;
    }

    return OK;
}

float DHT11::getHumidity() {
    // MSB always will be 0, so convert to 0 to reduce errors.
    this->bits[0] &= 0x7F;
    // For DHT11 this->bits[1] always will be 0.
    this->humidity = this->bits[0] * 1.0;
    return this->humidity;
}

float DHT11::getTemperature() {
    // MSB always will be 0, so convert to 0 to reduce errors.
    this->bits[2] &= 0x7F;
    // For DHT11 this->bits[3] always will be 0.
    this->temperature = this->bits[2] * 1.0;
    return this->temperature;
}

bool DHT11::isRealTime() {
    return this->realTime;
}
