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
#include <stdio.h>
#include <signal.h>

static int tag = 1;
// The SIGINT will break the loop.
void stopSignal() {
    tag = 0;
}

int main(void) {
    printf("\nThis awesome application started.\n");
    // Catch signal interruption SIGINT.
    signal(SIGINT, stopSignal);
    // Wiring Pi library setup.
    wiringPiSetup();
    // Set pin GPIO 21 (pin 29) as output.
    pinMode(29, OUTPUT);
    while(tag) {
        // Turn on the GPIO 21.
        digitalWrite(29, HIGH);
        // Pause during 0.5 seconds.
        delay(500);
        // Turn off the GPIO 21.
        digitalWrite(29,  LOW);
        // Pause during 0.5 seconds.
        delay(500);
    }
    printf("\nThis awesome application finished.\n");
    return 0;
}
