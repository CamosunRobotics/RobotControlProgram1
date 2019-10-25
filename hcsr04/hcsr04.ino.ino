/*
  HCSR04 - Library for arduino, for HC-SR04 ultrasonic distance sensor.
  Created by Martin Sosic, June 11, 2016.
*/

#include "Arduino.h"
#include "HCSR04.h"

UltraSonicDistanceSensor::UltraSonicDistanceSensor(
  int singlePin) {
  this->pulsePin = pulsePin;
}

float UltraSonicDistanceSensor::measureDistanceCm() {
  // Make sure that trigger pin is LOW.

  


  pinMode(pulsePin, OUTPUT);
  digitalWrite(pulsePin, LOW);
  delayMicroseconds(2);
  digitalWrite(pulsePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pulsePin, LOW);
  pinMode(pulsePin, INPUT);

  float distanceCM = (pulseIn(pulsePin, HIGH) * 100.0 * 3.43 / 1000.0 / 2.0)
  if (distanceCm <= 4) {
    return -1.0 ;
  }
  else if (distanceCm > 400) {
    return -2.0;
  } else {
    return distanceCm;
  }





  pinMode(pin, OUTPUT);
  digitalWrite(pulsePin, LOW);
  delayMicroseconds(2);
  // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
  digitalWrite(pulsePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pulsePin, LOW);
  // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
  //First set pin to input
  pinMode(pulsePin, INPUT);
  unsigned long durationMicroSec = pulseIn(pulsePin, HIGH);
  float distanceCm = durationMicroSec / 2.0 * 0.0343;
  if (distanceCm <= 4 || distanceCm > 400) {
    return -1.0 ;
  } else {
    return distanceCm;
  }
}
