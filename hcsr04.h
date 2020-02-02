/*
Created by Jeremy Lakes-Gardner Jan 28 2020
*/

#ifndef HCSR04_H
#define HCSR04_H

#include "Arduino.h"

class UltraSonicDistanceSensor {
 public:
    UltraSonicDistanceSensor();
    
    static int getDis(char pin);

 
};

#endif // HCSR04_H
