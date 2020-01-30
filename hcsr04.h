/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
*/

#ifndef HCSR04_H
#define HCSR04_H

#include "Arduino.h"

class UltraSonicDistanceSensor {
 public:
    /**
     * @param pin  Digital pin that is used for controlling sensor (trigger and echo connected together).
     */
    UltraSonicDistanceSensor(char pin);

    /**
     * Measures distance by sending ultrasonic waves and measuring time it takes them
     * to return.
     * @returns Distance in centimeters, or negative value if distance is greater than 400cm.
     */
    signed long measureDistanceCm();
 private:
    char pulsePin;// pin;
};

#endif // HCSR04_H
