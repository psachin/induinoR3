/*  Induino R3 User Guide - Program 11.0 - Interfacing with the Simple Labs DS1307 RTC Module */


#include <Wire.h> // I2C Library

#define myrtc 0x68 // I2C Address of DS1307

char *dow[]={
  " ","MON","TUE","WED","THU","FRI","SAT","SUN"}; // An Array to store the DAY text to match with the DAY parameter of the RTC

char *mode[]={
  "HR","AM","PM"}; // An Array to store the time mode 

int dd,mm,yy,day,hh,mins,ss,mde; // Variables to store the retrieved time value

void setup()
{
  Serial.begin(9600); // Initialise Serial Communication
  Wire.begin(); // Initialise Wire Communication - Join the I2C Bus
  delay(500);
  set_time(14,01,14,2,10,34,50,2); // Call the set_time function to set the intial time.
}

void loop()
{
  get_time();
  Serial.print(dd);
  Serial.print("/");
  Serial.print(mm);
  Serial.print("/");
  Serial.print(yy);
  Serial.print(" "); 
  Serial.print(dow[day]);
  Serial.print(" ");
  Serial.print(hh);
  Serial.print(":"); 
  Serial.print(mins);
  Serial.print(":");
  Serial.print(ss);
  Serial.print(" ");
  Serial.print(mode[mde]);  
  Serial.println();
  delay(1000);
}


// The set_time function takes parameters in the order of date, month, year, day of week, hours, minutes, seconds & mode
// the mode can have 3 possible values  (0=>24HR, 1=> AM, 2 => PM)

void set_time(int sdd, int smm, int syy, int sday, int shr, int smin, int ssec, int smode)
{
  Wire.beginTransmission(myrtc); // Initialise transmission to the myrtc I2C address
  Wire.write(0x00); // Write the value of the register to start with, 0 in this case represented in BCD format
  Wire.write(dec_to_bcd(ssec));  // convert the seconds value from decimal to bcd and write it to the seconds register
  // after the write operation the register pointer will be at the next register, so we do not have to set the value of the register again
  Wire.write(dec_to_bcd(smin));  // convert the minutes value from decimal to bcd and write it to the minutes register
  if(smode == 0) // Check if the mode is 24hrs mode
  {
    Wire.write(dec_to_bcd(shr));  // if 24 hours mode is on then convert the hours value from decimal to bcd and write it to the hours register
  }
  else // if the mode is 12 hr mode
  {
    // If 12 hour mode is selected then the 12 Hour mode bit (the 6th bit) has to be set to 1
    // convert the hour value to bcd first and then adding 64(2^6) to the converted hrs value will set the 6th bit HIGH

    shr = dec_to_bcd(shr)+64; 

    if(smode == 1) // check if it is AM
      Wire.write(shr); // if it is AM we can directly write the value of the above modified hours values to the hours register
    if(smode == 2) // check if it is PM
      Wire.write(shr+32); // If it is PM, then adding 32 (2^5) sets the 5th bit (the PM indication bit) HIGH, the calculated value is written to the hours register
  }
  Wire.write(dec_to_bcd(sday));  // convert the day value from decimal to bcd and write it to the day register
  Wire.write(dec_to_bcd(sdd));  // convert the date value from decimal to bcd and write it to the date register
  Wire.write(dec_to_bcd(smm));  // convert the month value from decimal to bcd and write it to the month register
  Wire.write(dec_to_bcd(syy));// convert the year value from decimal to bcd and write it to the year register
  Wire.endTransmission();  // end the transmission with the I2C device

}


// the get_time() function will retrieve the current time from the RTC and store it in the Global Variables declared

void get_time()
{
  Wire.beginTransmission(myrtc); // Initialise transmission to the myrtc I2C address
  Wire.write(0x00); // Write the value of the register to start with, 0 in this case represented in BCD format
  Wire.endTransmission(); // end the transmission with the I2C device
  Wire.requestFrom(myrtc, 7);  // Now ask the I2C device for 7 Bytes of Data // This corresponds to the values of the 7 registers starting with the 0th register 

  ss = bcd_to_dec(Wire.read()); // The first read will retrieve the value from the register address 0x00 or the seconds register, this is in the BCD format, convert this back to decimal
  mins = bcd_to_dec(Wire.read());// The second read will retrieve the value from the register address 0x01 or the minutes register, this is in the BCD format, convert this back to decimal
  hh = Wire.read();// The third read will retrieve the value from the hours register, this value needs to be processed for the 24/12 hr mode

  // Check of if the BCD hours value retrieved is greater than 35 (this indicates that the hours is in 12 hour mode
  // 35 is the maximum BCD value possible in the 24hr mode
  if(hh > 35) 
  {
    hh = hh - 64; // in the 12 Hours Mode the 12 hour mode bit (6th bit) is set to high, so we need to subtract 2^6 from our hours value
    if(hh > 32)// Now check if the hour value is greater than 32 (2^5 = 32) (this indicates that PM bit (5th bit) is high)
    {
      mde = 2; // Set the mde variable to indicate PM
      hh = hh-32; // subtract 32 from the hours value 
    }
    else // if the hour value is less than 32 it means that its in the AM mode
    {
      mde = 1; // Set the mde variable to indicate AM
    }   
  }
  else // if the 12 hour mode bit was not set, then the hour is in the 24 hour mode
  {
    mde = 0; // Set the mde variable to indicate 24 Hours
  }

  hh = bcd_to_dec(hh); // Convert the final hour value from BCD to decimal and store it back into the same variable
  day = bcd_to_dec(Wire.read());// The fourth read will retrieve the value from the register address 0x03 or the day register, this is in the BCD format, convert this back to decimal
  dd = bcd_to_dec(Wire.read());// The fifthread will retrieve the value from the register address 0x04 or the date register, this is in the BCD format, convert this back to decimal
  mm = bcd_to_dec(Wire.read());// The sixth read will retrieve the value from the register address 0x05 or the month register, this is in the BCD format, convert this back to decimal
  yy = bcd_to_dec(Wire.read());// The seventh read will retrieve the value from the register address 0x06 or the year register, this is in the BCD format, convert this back to decimal

}


// The dec_to_bcd() function converts a given decimal number to BCD format

int dec_to_bcd(int dec)
{
  return dec/10*16 + (dec%10); // convert and return the number from decimal to bcd format
}



// The dec_to_bcd() function converts a given BCD number to decimal format

int bcd_to_dec(int bcd)
{
  return bcd/16*10 + (bcd%16); // convert and return the number from bcd to decimal format
}
