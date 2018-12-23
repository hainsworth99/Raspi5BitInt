/* Harold Ainsworth
*  Winter 2018
*  A simple Raspberry Pi project that allows a user to display a 5-bit signed integer on a
*  display of 5 LEDs, one for the sign bit, and four for the value bits.
*/
#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>

// The min/max values of a 5-bit signed integer
const int min = -16;
const int max = 15;

// Pin number declarations using Broadcom chip pin numbers
const int signPin = 18;
const int eightPin = 19;
const int fourPin = 20;
const int twoPin = 21;
const int onePin = 22;
const int addPin = 17;
const int subPin = 16;

// SIGINT handler to make sure the LEDs get turned off before the program terminates
void SIGINT_handler(){
	digitalWrite(signPin, 0);
	digitalWrite(eightPin, 0);
	digitalWrite(fourPin, 0);
	digitalWrite(twoPin, 0);
	digitalWrite(onePin, 0);
	printf("Program terminated successfully.\n");
	exit(0);
}

/*
* Prints the given value to the LED display. If I had been working with a byte instead of
* 5 bits, this would have been waaay easier to write since I'm pretty sure there would have
* been an easier way of parsing the value to binary.
*/
void updateDisplay(int val){
	if (val >= 0){
		digitalWrite(signPin, 0);
		if (val - 8 >= 0){
			val -= 8;
			digitalWrite(eightPin, 1);
		} else digitalWrite(eightPin, 0);
		if (val - 4 >= 0){
                        val -= 4;
                        digitalWrite(fourPin, 1);
                } else digitalWrite(fourPin, 0);
		if (val - 2 >= 0){
                        val -= 2;
                        digitalWrite(twoPin, 1);
                } else digitalWrite(twoPin, 0);
		if (val - 1 >= 0){
                        val -= 1;
                        digitalWrite(onePin, 1);
                } else digitalWrite(onePin, 0);
	}
	else {
		digitalWrite(signPin, 1);
		int complement = -16;
		if (complement + 8 <= val){
			complement += 8;
			digitalWrite(eightPin,1);
		} else digitalWrite(eightPin,0);
		if (complement + 4 <= val){
                        complement += 4;
                        digitalWrite(fourPin,1);
                } else digitalWrite(fourPin,0);
		if (complement + 2 <= val){
                        complement += 2;
                        digitalWrite(twoPin,1);
                } else digitalWrite(twoPin,0);
		if (complement + 1 <= val){
                        complement += 1;
                        digitalWrite(onePin,1);
                } else digitalWrite(onePin,0);
	}
}

int main(int argc, char **argv){
	wiringPiSetupGpio(); // Initialize wiringPi using Broadcom pin numbering

	// Set bit pins as output
	pinMode(signPin, OUTPUT);
	pinMode(eightPin, OUTPUT);
	pinMode(fourPin, OUTPUT);
	pinMode(twoPin, OUTPUT);
	pinMode(onePin, OUTPUT);
	// Set button pins as input
	pinMode(addPin, INPUT);
	pinMode(subPin, INPUT);
	// Enable buttons
	pullUpDnControl(addPin, PUD_UP);
	pullUpDnControl(subPin, PUD_UP);

	signal(SIGINT, SIGINT_handler);

	// Value begins at 0
	int value = 0;

	// Main loop
	while (1){
		updateDisplay(value);
		if (value < max && !digitalRead(addPin)){ // increment only if less than max
			value++;
			printf("Value updated to: %d\n", value);
			delay(250);
		}
		else if (value > min && !digitalRead(subPin)){ // decrement only if greater than min
			value--;
			printf("Value updated to: %d\n", value);
			delay(250);
		}
	}

}

