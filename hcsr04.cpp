/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
  Modified by Jeremy Lakes-Gardner, Jan28, 2019
*/

#include "Arduino.h"
#include "HCSR04.h"

UltraSonicDistanceSensor::UltraSonicDistanceSensor(
        char pin) {
    this->pulsePin = pin;
}

signed long UltraSonicDistanceSensor::getDistanceCm() {
    // Go low first, then high, then low again
  pinMode(pulsePin, OUTPUT);
  digitalWrite(pulsePin, LOW);
  delayMicroseconds(2);//timing
  digitalWrite(pulsePin, HIGH);
  delayMicroseconds(10);//timing
  digitalWrite(pulsePin, LOW);
  pinMode(pulsePin, INPUT);
  
  //listen for response
  unsigned long durationMicroSec = pulseIn(pulsePin, HIGH);
  signed long distanceCm = durationMicroSec / 2.0 * 0.0343;
  if (distanceCm <= 4 || distanceCm > 400) {
      return -1 ;
  } else {
      return distanceCm;
  }
}
