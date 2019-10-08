// Tank-Style Sweep Sample
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
#define trigPin 13                                                              //trigger and echo pins for ultrasonic transducer
#define echoPin 12
#define maxPower 100

//functions

long sonic(void);                      //this function will send an output pulse and collect the returning data with the ultrasonic transducer.  function produces an integer, needs no input

long measure(long pulse);            //the data from the ultrasonic transducer is converted into a distance measurement
#include <SabertoothSimplified.h>

// Mixed mode is for tank-style diff-drive robots.
// Only Packet Serial actually has mixed mode, so this Simplified Serial library
// emulates it (to allow easy switching between the two libraries).

SabertoothSimplified ST; // We'll name the Sabertooth object ST.
// For how to configure the Sabertooth, see the DIP Switch Wizard for
//   http://www.dimensionengineering.com/datasheets/SabertoothDIPWizard/start.htm
// Be sure to select Simplified Serial Mode for use with this library.
// This sample uses a baud rate of 9600.
//
// Connections to make:
//   Arduino TX->1  ->  Sabertooth S1
//   Arduino GND    ->  Sabertooth 0V
//   Arduino VIN    ->  Sabertooth 5V (OPTIONAL, if you want the Sabertooth to power the Arduino)
//
// If you want to use a pin other than TX->1, see the SoftwareSerial example.

void setup()
{
  SabertoothTXPinSerial.begin(9600); // This is the baud rate you chose with the DIP switches.

  ST.drive(0); // The Sabertooth won't act on mixed mode until
  ST.turn(0);  // it has received power levels for BOTH throttle and turning, since it
  // mixes the two together to get diff-drive power levels for both motors.
  // So, we set both to zero initially.

  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
}

// Mixed mode tips:
//   drive() should go forward and back, turn() should go right and left.
//     If this is reversed, swap M2A and M2B.
//   Positive on drive() should go forward, negative should go backward.
//     If this is reversed, swap A and B on both M1 and M2.
//   Positive on turn() should go right, negative should go left.
//     If this is reversed, swap M1 and M2.

// In this sample, the SLOW sweep (left-to-right) here is turning,
// and the FAST sweep (backwards-to-forwards) is throttle.
void loop()
{
  int power;

  long pulse;
  long distance;
  bool canMoveForward = false;
  bool canIncrementPower = false;
  long sysTime;
  sysTime = millis();

  /*  // Don't turn. Ramp from going backwards to going forwards, waiting 20 ms (1/50th of a second) per value.
    for (power = -127; power <= 127; power ++)
    {
      ST.drive(power);
      delay(20);
    }

    // Now, let's use a power level of 20 (out of 127) forward.
    // This way, our turning will have a radius. Mostly, the command
    // is just to demonstrate you can use drive() and turn() at the same time.
    ST.drive(20);

    // Ramp turning from full left to full right SLOWLY by waiting 50 ms (1/20th of a second) per value.
    for (power = -127; power <= 127; power ++)
    {
      ST.turn(power);
      delay(50);
    }

    // Now stop turning, and stop driving.
    ST.turn(0);
    ST.drive(0);

    // Wait a bit. This is so you can catch your robot if you want to. :-)
    delay(5000);

  */

  while (1) {

    pulse = sonic();
    distance = measure(pulse);


    if (millis() >= sysTime + 20) {

      sysTime = millis();
      canIncrementPower = true;

    }

    else {
      
      canIncrementPower = false;
    
    }

    if (distance <= 30) {

      power = 0;
      ST.drive(0);
      ST.turn(50);
    }

    if (distance > 30) {

      canMoveForward = true;
      ST.drive(power);
      ST.turn(0);

    }

    if (canMoveForward == true && canIncrementPower == true) {

      power = power + 1;
      if (power > maxPower) {
        power = maxPower;
      }

    }



  }


}

//////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS//
//////////////////////////////////////////////////////////////////////////////////////////////////


long sonic (void) {

  digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);                   //send a 10 microsecond pulse out from the ultrasonic transducer
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  long pulseTime = pulseIn(echoPin, HIGH);       //time the return pulse

  return pulseTime;                             //return the time taken by the pulse to return to the transducer
}



long measure(long pulse) {                  //use the pulse data to fijd distance

  long  range = pulse * 3.43 / 2;           //multiply by speed of sound (divided to get meters) and divide by 2 to account for the two way trip the sound waves must take
  range = range / 100;                      //divide by 100 to get centimeters
  //range = pulse*34 / 20;
  //range = range / 100;

  return range;                           //return the distance in cm

}
