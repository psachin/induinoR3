/*
  Induino R3 User Guide - Program 2.0 - LED State Toggle using Push
  Button
*/

int state = 0;

void setup()
{
  pinMode(7,INPUT_PULLUP); // declare the Button as INPUT pin with internal Pull up enabled
  pinMode(13,OUTPUT);  // declare LED pin as output pin

}

void loop()
{
  if(digitalRead(7)==0) // check if the button is being pressed
    {
      state =!state; // toggle the state variable
      digitalWrite(13,state); // write the value of the state variable to the led
      while(digitalRead(7)==0); // wait for the switch to be released - Part of Debounce
      delay(40); // give some time for the switch to settle back to normalcy - Part of Debounce
    }
}
