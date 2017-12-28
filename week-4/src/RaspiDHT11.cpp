/*
 * Author: Manuel Parra Z.
 * Date: 27/12/2017
 * License: MIT License
 * Hardware:
 *      - Raspberry Pi B+.
 *      - DHT11 DFRobot Sensor.
 * Description: Testing code for DHT11 library.
 */

#include <iostream>
#include "DHT11.h"

void main () {
    std::cout << "=================================================\n";
    std::cout << "DHT11 library for Raspberry Pi testing start now.\n";
    std::cout << "=================================================\n";
    std::cout << "\n";

    // GPIO 18 is pin 1.
    DHT11* sensor = new DHT11(1);
    DHT11_STATE state = sensor->read();

    if (state == OK) {
        float humidity = sensor->getHumidity();
        float temperature = sensor->getTemperature();
        std::cout << "=================================================\n";
        std::cout << "Temperature (°C): " << temperature;
        std::cout << " -- ";
        std::cout << "Humidity (%): " << humidity;
        std::cout << "\n";
        std::cout << "=================================================\n";
    } else {
        std::cout << "ERROR CODE: " << state;
    }

    delete(sensor);
}
