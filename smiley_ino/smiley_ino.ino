#include <LiquidCrystal.h>

// initialize the lcd
LiquidCrystal lcd(8,9,10,11,12,13);

byte mySmiley[8] = {0,10,0,100,100,17,14,0}; // Define the smiley character

void setup() {
// add mySmiley character to 0th location of the LCD's CGRAM;
// 0-7 are possible values here
lcd.createChar(0, mySmiley);

// set up number of column and rows
lcd.begin(16, 2);

// Write out Smiley Character.
// Type casting is required as we are directly mentioning a value
lcd.write((uint8_t)0);
}

void loop() {}

