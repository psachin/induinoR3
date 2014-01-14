// Print LDR values to serial o/p

int ldr_val = 0;		// var to store LDR value.
int ldr_max_val = 1023;

void setup() {
  Serial.begin(9600);		// begin serial communication.
}

void loop() {
  ldr_val = analogRead(3);	// read pin 3
  Serial.print("Current LDR value: ");
  Serial.println(ldr_val);
  delay(1000);			// 1 sec delay(DO NOT remove)
}
