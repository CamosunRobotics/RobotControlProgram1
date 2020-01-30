#include <wiringPi.h>
#include <stdio.h>


#define pin1 4
#define pin2 1

/*Basic Program for the raspberry pi to use GPIO pins
 * 
 * 
 * wiringpi uses its own pin numbers, found here: https://hackage.haskell.org/package/wiringPi
 * 
 *
 *using:
 *sudo apt-get install wiringpi
 *
 * 
 *compiled with:
 *gcc -Wall -o gpiotest gpiotest.c -lwiringPi
 * 
 */

int main(void)
{
	wiringPiSetup();
	
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	
	//# of repetitions:
	int t = 90;
	
	while(t)
	{
	
	if(t){
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, LOW);
	delay(500);
	digitalWrite(pin1, LOW);
	digitalWrite(pin2, HIGH);
	delay(500);}
	
	
	t--;
	}
	return 0;
}
