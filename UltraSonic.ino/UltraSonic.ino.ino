
#define uSonic1 10
#define uSonic2 9
#define servo1pin 8
#define servo2pin 7
#include <Servo.h>

Servo sonicServo1;


long sonicTime(char uSonic);
long sonicCM(char uSonic);

void setup()
{
  Serial.begin(9600);
  
  pinMode(uSonic1, OUTPUT);
  pinMode(uSonic2, OUTPUT);


}

void loop()
{

  Serial.println(sonicMeters(uSonic2));
  delay(200);

}

long sonicTime(char uSonic)
{ // The same pin is used to read the signal

  pinMode(uSonic, OUTPUT);
  digitalWrite(uSonic, LOW);
  delayMicroseconds(2);
  digitalWrite(uSonic, HIGH);
  delayMicroseconds(10);
  digitalWrite(uSonic, LOW);
  pinMode(uSonic, INPUT);

  return (pulseIn(uSonic, HIGH));
}
long sonicCM(char uSonic)
{
  return(sonicTime(uSonic) * 100* 3.43 / 1000.0 / 2.0);
}
