/*

  Created by Jeremy Lakes-Gardner, Jan 28, 2019
*/

#include "Arduino.h"
#include "hcsr04.h"

//constructor
UltraSonicDistanceSensor::UltraSonicDistanceSensor()
{  
}

int UltraSonicDistanceSensor::getDis(char pin)
{
    //yell out a signal
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);//timing
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);//timing
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  
    //listen for response
  unsigned long durationMicroSec = pulseIn(pin, HIGH);
  signed long distanceCm = durationMicroSec / 2.0 * 0.0343;
  if (distanceCm <= 4 || distanceCm > 400) {//valid range is 5-400cm
      return -1 ;
  } else {
      return distanceCm;
      
  }
  
}
/*

*/
