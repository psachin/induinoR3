// blink RGB

void setup() {
  // blank
}

/*

  5/255=0.091 V(~20mV)
  
*/

void loop() {
  analogWrite(3, 153);		// BLUE(~3V)
  analogWrite(5, 51);		// GREEN(~1V)
  analogWrite(6, 51);		// RED(~1V)
}
