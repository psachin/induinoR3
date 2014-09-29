/*
  Morse.h - Library for flashing Morse code.
  Created as a self tutorial by Sachin Patil, Sep 29, 2014.
  Released under GNU GPL version 3 or later.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
public:
    Morse(int pin);
    void dot();
    void dash();
private:
    int _pin;
};

#endif
