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
#include <string>
#include <unistd.h>
#include "DHT11.h"

int main () {
    std::cout << "=================================================\n";
    std::cout << "DHT11 library for Raspberry Pi testing start now.\n";
    std::cout << "=================================================\n";
    std::cout << "\n";

    // GPIO 18 is pin 1.
    DHT11* sensor = new DHT11(1);
    std::string realTime = ((sensor->isRealTime() == true) ? "ENABLE" : "DISABLE");
    std::cout << "Real Time: " << realTime << "\n";

    int ok = 0;
    int error = 0;
    for (int i= 0; i < 100; i++) {
        DHT11_STATE state = sensor->read();

        if (state == OK) {
            float humidity = sensor->getHumidity();
            float temperature = sensor->getTemperature();
            std::cout << "Temperature (°C): " << temperature;
            std::cout << " -- ";
            std::cout << "Humidity (%): " << humidity;
            std::cout << ".\n";
            ok++;
        } else {
            std::cout << "ERROR CODE: " << state;
            std::cout << ".\n";
            error++;
        }
        
        sleep(10);
    }

    std::cout << "=================================================\n";
    std::cout << "                S T A T I S T I C S              \n";
    std::cout << "\n";
    std::cout << "OK Signals: " << ok;
    std::cout << " -- ";
    std::cout << "ERROR Signals: " << error;
    std::cout << ".\n";
    std::cout << "=================================================\n";
   
    delete(sensor);

    return 0;
}
