/*
 * Author: Manuel Parra Z.
 * Date: 23/12/2017
 * License: MIT License
 * Hardware:
 *      - Arduino ONE R3.
 *      - DHT11 DFRobot Sensor.
 * Description: C++ library for DHT11 DFRobot Sensor.
 */

#ifndef DHT11_H
#define DHT11_H

#define DHT11_VERSION "0.0.1"

#include <Arduino.h>

enum DHT11_STATE {
    OK,
    ERROR_CHECKSUM,
    ERROR_CONNECTION_L,
    ERROR_CONNECTION_H,
    ERROR_ACK_L,
    ERROR_ACK_H
};

class DHT11 {

    private:
        int pin;
        uint8_t bits[5];
        unsigned long timeout;
        float humidity;
        float temperature;

    public:
        DHT11(int _pin);
        DHT11_STATE read();
        float getHumidity();
        float getTemperature();
};
#endif
