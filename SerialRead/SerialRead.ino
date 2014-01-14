/*  Induino R3 User Guide - Program 3.1 - Serial Input / Button controlled Binary Counter with Serial Print
 This sketch increases a 3 bit number every time a button is pressed by the user and shows the output on 3 LEDs   
 */

int i = 0;  
char txt[]="The Current Value is : "; // A string stored in a character array
void setup()  
{  
  pinMode(11,OUTPUT);   // declare LED pins as output pins  
  pinMode(12,OUTPUT);  
  pinMode(13,OUTPUT);  
  pinMode(7,INPUT_PULLUP);// declare the Button as INPUT pin with internal Pull up enabled
  Serial.begin(9600); // initialize Serial Communication
  Serial.println("Starting the Program");// This will be printed only once
}  
void loop()  
{  
  if(digitalRead(7)==0 || Serial.available()>0)  // if the button is pressed  or Serial data is received
  {
    if(digitalRead(7)==0) // if the button is pressed
    {  
      if(i<7)        // if counter value is less than 7 or 3 bits  
        i++;        // increment counter value  
      else           
        i=0;        // reset counter to 0  
      while(digitalRead(7)==0);  // wait till button is released to avoid incrementing the counter again  
      delay(100);         // small delay to avoid debounce  
    }
    if(Serial.available()>0) // if Serial data is received
    {
      int val = Serial.read(); // read 1 byte of data and store in the integer variable val. if the user sent 1, the ascii value for 1 is 49 so val will have the value 49
      val = val - 48; // 48 is the ascii value for 0. So if we did receive a 0 subtracting 48 would make the value of val as 0, same is true for the remaining numbers
      if(val>=0 && val <=7)// Check if Val is in the range of 0 to 7, we can display only values in this range and ignore all other values
      {
        i = val; // assign the counter to the value received from the Serial Port
      }

    }
    Serial.print(txt); // Print Descriptive test from the character array
    Serial.println(i); // print the current value
    int a=i%2;      // calculate LSB   
    int b=i/2 %2;     // calculate middle bit  
    int c=i/4 %2;     // calculate MSB   
    digitalWrite(11,a);  // write LSB 
    digitalWrite(12,b);  // write middle bit  
    digitalWrite(13,c);  // write MSB  
  }  
}


