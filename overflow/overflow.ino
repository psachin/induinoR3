/*
  HC-SR04 Ultrasonic Sensor Interface for water overflow alert with
  wireless interation via remote-control
*/
int pingPin = 16; // A2 - Connected to both Trig & ECHO Pins of the Sensor
int pinSpeaker = 10; //Set up a speaker on a PWM pin (digital 9, 10, or 11)

int warningLED = 11; // choose the pin for the sound LED
int pauseLED = 12; // Indicates the loop has pause

int warningLevel = 3;
int criticalLevel = 1;


void setup() {
  pinMode(warningLED, OUTPUT);  // declare sndLED as output
  pinMode(pinSpeaker, OUTPUT);
  pinMode(15,INPUT); // TSOP is connected on the 15ht pin
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  int remote_val = remote(); // Call remote function

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH); // Sending a High Pulse on the Trig Pin of the Sensor
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);


  if(remote_val>0 && remote_val==149) {
     pauseScaning();
     Serial.println("Remote value: ");
     Serial.print(remote_val);
     Serial.println("");
  }

  Serial.print(inches);
  Serial.print(" in ");
  if(inches <= warningLevel) {
      Serial.println("(WARNING!)");
      startWarning(inches);
      // Serial.println();
  }
  // Serial.print(cm);
  // Serial.print("cm");
  Serial.println();
  digitalWrite(warningLED, LOW);
  delay(100);
}


long microsecondsToInches(long microseconds) {
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet
    // per second). This gives the distance travelled by the ping,
    // outbound and return, so we divide by 2 to get the distance of
    // the obstacle. See:
    // http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
    return microseconds / 74 / 2;
}


long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per
    // centimeter. The ping travels out and back, so to find the
    // distance of the object we take half of the distance travelled.
    return microseconds / 29 / 2;
}


void playTone(long duration, int freq) {
    // duration in mSecs, frequency in hertz
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


void startWarning(long inches) {
  if(inches <= criticalLevel) {
      Serial.println("(WARNING!)");
      playTone(300, 160);
      // Serial.println();
  }

  digitalWrite(warningLED, HIGH);
  playTone(300, 160);
}


void pauseScaning() {
    Serial.println("Pausing for 5 sec..");
    digitalWrite(pauseLED, HIGH);
    delay(5000);
    digitalWrite(pauseLED, LOW);
}


// A Dedicated function that will calculate and return a decimal value
// for each of the buttons on a remote.
int remote()  {
  int value = 0;  // a Variable to store our final calculated value
  int time = pulseIn(15,LOW);  // we need to look for the duration of
			       // the LOW pulse as TSOP will invert
			       // the incoming HIGH pulse
  if(time>2000) {
      // Checking if the Start Bit has been received. Start
      // Bit Duration is 2.4ms
      for(int counter1=0;counter1<12;counter1++) {
	  // A loop to receive the next 12 bits The loop is in the
	  // inverse order as we will be receiving the MSB
	  //Serial.println(counter1);
	  if(pulseIn(15,LOW)>1000) {
	      // checking the duration of each pulse, if it is a '1'
	      // then we use it in our binary to decimal conversion,
	      // '0's can be ignored.
	      // Serial.println(counter1);
	      value = value + (1<< counter1);
	      // binary to decimal
	      // conversion. 1<< i is nothing
	      // but 2 raised to the power of
	      // i
	      //Serial.print("Value: ");
	      //Serial.println(value);
	  }
      }
  }
  return value;
}
