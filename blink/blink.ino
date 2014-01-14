// Blink LED on pin 11

int RED = 11;
int GREEN = 12;
int WHITE = 13;

void setup() {
  pinMode(RED, OUTPUT);		// Set Pin 11 as output pin
  pinMode(GREEN, OUTPUT);
  pinMode(WHITE, OUTPUT);
}

void loop() {
  digitalWrite(RED, HIGH);	// PIN 11 to HIGH
  delay(1000);			// delay of 1000 ms
  digitalWrite(RED, LOW);	// PIN 11 to HIGH
  digitalWrite(GREEN, HIGH);	// PIN 11 to HIGH
  delay(1000);			// again delay of 1000 ms
  digitalWrite(GREEN, LOW);	// PIN 11 to HIGH
  digitalWrite(WHITE, HIGH);	// PIN 11 to HIGH
  delay(1000);			// again delay of 1000 ms
  digitalWrite(WHITE, LOW);	// PIN 11 to HIGH
}
