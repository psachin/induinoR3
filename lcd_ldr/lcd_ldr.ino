/*
  LDR Based Lighting Level Controller This is a simple program where 3
  LEDS are switched ON / OFF one by one as the Light Intensity Sensed
  by the LDR Decreases / Increases
*/

/* Pin Mappings of LCD shield
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 10
 * LCD D5 pin to digital pin 11
 * LCD D6 pin to digital pin 12
 * LCD D7 pin to digital pin 13
 * LCD R/W pin to ground
 */

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins from the above pin mappings
LiquidCrystal lcd(8,9,10,11,12,13); // 

#define threshold1 350 // First Threshold Value of Darkness above which the first LED is switched ON  
#define threshold2 650 // Second Threshold Value of Darkness above which the second LED is switched ON  
#define threshold3 950 // Third Threshold Value of Darkness above which the third LED is switched ON  

int val = 0; // A Variable to Store the Light Value from the LDR  
void setup()  
{
  lcd.begin(16,2);		// chars,lines
  pinMode(11,OUTPUT); // LED 1   
  pinMode(12,OUTPUT); // LED 2  
  pinMode(13,OUTPUT); // LED 3  
  Serial.begin(9600);// Start a Serial Connection  
}  
void loop()  
{
  lcd.clear();
  val = analogRead(3);// Reads a 10-bit value corresponding to the
		      // voltage applied on analog input pin 3.
  Serial.print("Light Intensity is :");// Prints the given string /
				       // value to the serial monitor
  lcd.print("Light : ");
  lcd.print(val);
  Serial.println(val);// prints the value of the variable val to the
		      // serial monitor and moves the cursor to the
		      // next line (the ln part of println does this
  if(val > threshold1) // Checks & Turns the First LED ON / OFF based on Light Intensity  
    digitalWrite(11,HIGH);  
  else  
    digitalWrite(11,LOW);  
  if(val > threshold2) // Checks & Turns the Second LED ON / OFF based
		       // on Light Intensity
    digitalWrite(12,HIGH);  
  else  
    digitalWrite(12,LOW);  
  if(val > threshold3) // Checks & Turns the Thirdf LED ON / OFF based
		       // on Light Intensity
    digitalWrite(13,HIGH);  
  else  
    digitalWrite(13,LOW);

  delay(2000);
}  
