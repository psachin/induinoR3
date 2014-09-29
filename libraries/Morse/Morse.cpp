/*
  Morse.c - Library for flashing Morse code.
  Created as a self tutorial by Sachin Patil, Sep 29, 2014.
  Released under GNU GPL version 3 or later.
*/
#include "Arduino.h"
#include "Morse.h"


Morse::Morse(int pin)		// Constructor
{
    pinMode(pin, OUTPUT);
    _pin = pin;
}


void Morse::dot()
{
    digitalWrite(_pin, HIGH);
    delay(250);
    digitalWrite(_pin, LOW);
    delay(250);
}


void Morse::dash()
{
    digitalWrite(_pin, HIGH);
    delay(1000);
    digitalWrite(_pin, LOW);
    delay(250);
}
