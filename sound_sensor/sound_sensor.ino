/*
  This is the code to make a LED blink with the music.  You have to
  set the threshold so it' sensible enough to make the led blink.
  
  You connect an LED to PIN13 and the Sound Sensor to Analog Pin 0
*/
 
int led = 13;
int threshold = 413; //Change This
int volume;

void setup() {                
  Serial.begin(9600); // For debugging
  pinMode(led, OUTPUT);     
}

void loop() {
  
  volume = analogRead(A0); // Reads the value from the Analog PIN A0
  
  //Debug mode
  Serial.println(volume);
  delay(100);
  
  if(volume>=threshold){
    digitalWrite(led, HIGH); //Turn ON Led
  }  
  else{
    digitalWrite(led, LOW); // Turn OFF Led
  }

}
