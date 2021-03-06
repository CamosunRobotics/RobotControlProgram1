
// Tank-Style Sweep Sample
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
                                                            
#define sonic1 12 //trig and echo pins are connected togther and to this pin
#define maxPower 50


//functions

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

//Global variables
//struct piData {
//  
//  char commandCode[30];
//  unsigned int payloadSize;
//  char payload[];
//  char checksum[15];
//  
//}incomingData;


//Prototypes:
int getDis(char pin);
struct piData handlePiSerial(void);
void handlePiCommand(struct piData);
void go(signed int relativeSpeed);


//for ST.turn, negatives turn to the right, positives to the left


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

    int testTime = 15;
    while(testTime)
    {
    //distance = getDis(sonic1);
    //if(distance > 30)
      {
      delay(10);
      go(80);
      //delay(7000);
      //ST.drive(40);
      
     // ST.turn(30);
      testTime--;
      }
    }
  }
}

//    incomingData = handlePiSerial();
//    handlePiCommands(incomingData);
    
//    Serial.println(incomingData.commandCode);
    
    
//    distance = getDis(sonic1);


//    if (millis() >= sysTime + 20) {
//
//      sysTime = millis();
//      canIncrementPower = true;
//
//    }
//
//    else {
//      
//      canIncrementPower = false;
//    
//    }
//
//    if (distance <= 30) {
//
//      power = 0;
//      ST.drive(0);
//      ST.turn(50);
//    }
//
//    if (distance > 30) {
//
//      canMoveForward = true;
//      ST.drive(power);
//      ST.turn(0);
//
//    }
//
//    if (canMoveForward == true && canIncrementPower == true) {
//
//      power = power + 1;
//      if (power > maxPower) {
//        power = maxPower;
//      }
//
//    }
//
//  }
//
//}

//////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS//
//////////////////////////////////////////////////////////////////////////////////////////////////

void go(signed int relativeSpeed)//experimentally tested, don't mess with this unless you know what you are doing
{
  int t = 8;
  while(t)
  {
  ST.drive(relativeSpeed);
  delay(25);
  ST.turn(0);
  ST.drive(0);
  ST.turn(14);
  //for turn:
  //at 20 turns left 
  //14 seems to be the sweet spot
  //7 turns slightly right
  delay(11);
  ST.turn(0);
  ST.drive(0);
  t--;
  }
  delay(2);
  
}



int getDis(char pin)//returns the distance in cm
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
  signed long distanceCm = pulseIn(pin, HIGH) / 2.0 * 0.0343;
  if (distanceCm <= 4 || distanceCm > 400) {//valid range is 5-400cm
      return -1 ;
  } else {
      return distanceCm;
  }
}
