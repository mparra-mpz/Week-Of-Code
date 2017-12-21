/*
 * Author: Manuel Parra Z.
 * Date: 22/11/2017
 * License: MIT License
 * Hardware:
 *      - Raspberry Pi B+
 *      - LED
 *      - 220 Resistance
 * Description: Project to turn on/off a led using a Raspberry.
 * Link: https://github.com/mparra-mpz/Week-Of-Code/wiki/Week-1:-Raspberry-Led-Control
 */

// Add the Wiring Pi library.
#include <wiringPi.h>

int main(void) {
    // Wiring Pi library setup.
    wiringPiSetup();
    // Set pin GPIO 21 (pin 29) as output.
    pinMode(29, OUTPUT);
    while(1) {
        // Turn on the GPIO 21.
        digitalWrite(29, HIGH);
        // Pause during 1 second.
        delay(1000);
        // Turn off the GPIO 21.
        digitalWrite(29,  LOW);
        // Pause during 1 second.
        delay (500) ;
    }

    return 0 ;
}
