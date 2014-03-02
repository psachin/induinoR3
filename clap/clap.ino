/*
  Enable sound when motion is detected.
 */ 
 
int pirLED = 11;                // choose the pin for the PIR LED
int sndLED = 12;		// choose the pin for the sound LED
int pirPin = 2;               // choose the input pin (for PIR sensor)

int threshold = 413; // sound threshold
int volume;

int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)

void setup() {
  pinMode(pirLED, OUTPUT);      // declare pirLED as output
  pinMode(sndLED, OUTPUT);      // declare sndLED as output
  pinMode(pirPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pirPin);  // read input value
  Serial.println(val);
  
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(pirLED, HIGH);  // turn LED ON
    // playTone(300, 160);
    startListening();
    delay(150);

    /*
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
    */
    
  } else {
    digitalWrite(pirLED, LOW); // turn LED OFF
    //playTone(0, 0);
    //delay(300);

    /*
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
    */
  }
  
}

// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

void startListening() {
  volume = analogRead(A0); // Reads the value from the Analog PIN A0
  
  //Debug mode
  Serial.println(volume);
  // delay(100);
  
  if(volume>=threshold){
    digitalWrite(sndLED, HIGH); //Turn ON Led
    playTone(300, 160);		// also sound buzzer
  }  
  else{
    digitalWrite(sndLED, LOW); // Turn OFF Led
  }
}

