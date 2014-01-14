/*  Induino R3 User Guide - Program 10.1 - Interfacing a Character LCD using the LCD Shield to display Distance value on the LCD */
/* Pin Mappings as per the Simple Labs' LCD shield
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 10
 * LCD D5 pin to digital pin 11
 * LCD D6 pin to digital pin 12
 * LCD D7 pin to digital pin 13
 * LCD R/W pin to ground
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9,10,11,12,13);

const int pingPin = 16; // HCSR-04 is connected to the sensor Interface A2 aka 16

long ol_inches=0, ol_cm=0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

}

void loop() {
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The HCSR 04 is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the HCSR 04: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //if(cm!=ol_cm || inches!=ol_inches)  // Check if the new dsitance values are not the same as the old values
  {
  lcd.clear(); // Clear the Dispaly
  lcd.print(inches); // Print the Distance in Inches
  lcd.setCursor(4, 0); // Position the cursor of the LCD display to print from the 5th Character on the First Line
  lcd.print("INCHES");// Print the descriptive text
  lcd.setCursor(0, 1); // Position the cursor of the LCD display to print from the 1st Character on the Second Line
  lcd.print(cm); // Print the Distance in Centimeters
  lcd.setCursor(4, 1);// Position the cursor of the LCD display to print from the 5th Character on the Second Line
  lcd.print("CMS"); // Print the descriptive text
  ol_inches = inches; // store the new inches value into a variable
  ol_cm = cm; // store the new centimeters value into a variable
  delay(200);
  
}
  
  // print the number of seconds since reset:
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
