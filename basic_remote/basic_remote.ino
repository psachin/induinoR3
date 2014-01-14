/* TSOP Remote Receiver Program for Sony Remote*/

void setup()  
{  
  pinMode(15,INPUT); // TSOP is connected on the 15ht pin  
  Serial.begin(9600);  
}

void loop()  
{  
  int remote_val = remote();  // Call the remote function to get the
			      // value of the key pressed
  if(remote_val>0)  // check if the value is greater than 0. A 0 means
		    // that no signal was received by the TSOP
  {  
    Serial.println(remote_val);  
    delay(150); // A remote press will normally generate 3 signal
		// trains. This is to avoid reading duplicates
  }
}


// A Dedicated function that will calculate and return a decimal value
// for each of the buttons on a remote.
int remote()  
{  
  int value = 0;  // a Variable to store our final calculated value
  int time = pulseIn(15,LOW);  // we need to look for the duration of
			       // the LOW pulse as TSOP will invert
			       // the incoming HIGH pulse
  if(time>2000) // Checking if the Start Bit has been received. Start
		// Bit Duration is 2.4ms
  {  
    for(int counter1=0;counter1<12;counter1++) // A loop to receive
					       // the next 12 bits The
					       // loop is in the
					       // inverse order as we
					       // will be receiving
					       // the MSB
    {  
      Serial.println(counter1);
      if(pulseIn(15,LOW)>1000) // checking the duration of each pulse,
			       // if it is a '1' then we use it in our
			       // binary to decimal conversion, '0's
			       // can be ignored.
      { 
       Serial.println(counter1); 
        value = value + (1<< counter1);// binary to decimal
				       // conversion. 1<< i is nothing
				       // but 2 raised to the power of
				       // i
        Serial.print("Value: ");
	Serial.println(value);
      }  
    }  
  }  
  return value;  
}  

