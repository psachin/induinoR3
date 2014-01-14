// Push Button Binary counter

/*
  This sketch increases a 3 bit number every time a button is pressed
  by the user and shows the output on 3 LEDs.

  Prints a value on every button press.
*/

int i = 0;
char txt[] = "The current value is: ";
  
void setup() {
  pinMode(11,OUTPUT);   // declare LED pins as output pins
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(7, INPUT_PULLUP);
  Serial.begin(9600);		// initialize serial communication.
  Serial.println("Starting the Program"); // print only once.
}

void loop() {
  if (digitalRead(7)==0) {
    if(i<7) {
      i++;
    }
    else {
      i=0;
    }
    
    Serial.print(txt);
    Serial.println(i);		// print the current value.
    
    int a=i%2;      // calculate LSB
    int b=i/2 %2;     // calculate middle bit
    int c=i/4 %2;     // calculate MSB
    digitalWrite(11,a);  // write MSB
    digitalWrite(12,b);  // write middle bit
    digitalWrite(13,c);  // write LSB
    while(digitalRead(7)==0);
    delay(1000);     // wait for a second
  }
}
