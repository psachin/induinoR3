/*
  Change intensity on RGB-RED(PIN6) using push buttons.
 */

byte intensity = 0;		// I have used 'byte' variable type
				// since output has only 8 bit
				// resolution.

void setup() {
  pinMode(7, INPUT_PULLUP);	// to increment intensity
  pinMode(9, INPUT_PULLUP);	// to decrement intensity
}

void loop() {
  if(digitalRead(7)==0) {	// if pustBUtton is pressed
    if(intensity<255) {		// increase intensity only if it is not MAX
      intensity++;
    }
    else {
      intensity = 0;		// else, reset intensity.
    }
    delay(20);			// purposely
  }

  if(digitalRead(9)==0) {       // if pustBUtton is pressed
    if(intensity>0) {		
      intensity--;
    }
    else {
      intensity = 255;		// reset intensity.
    }
    delay(20);
  }

  analogWrite(6, intensity);	// finally write intensity on pin6
}
