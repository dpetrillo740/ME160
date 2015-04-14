/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define DO   6
#define CS   4
#define CLK  5
#define SOL  13
Adafruit_MAX31855 thermocouple(CLK, CS, DO);
bool SOLstatus;

//ADC Setup
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

void setup() {
  Serial.begin(115200);
  delay(500);
  
  pinMode(SOL, OUTPUT);
  digitalWrite(SOL, HIGH); // Why is the opposite of this true??
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, FlopSOL, FALLING);
   
  //Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  //Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  ads.setGain(GAIN_SIXTEEN);       // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
  
}

void loop() {
  // basic readout test, just print the current temp
  // Serial.print("Internal Temp = ");
  // Serial.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
    // Serial.println("Something wrong with thermocouple!");
    Serial.print(0);
   } else {
    // Serial.print("C = "); 
     Serial.print(c);
   }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFarenheit());
   
   Serial.print(" ");
   
   int16_t results;
   float multiplier = 0.0078125F; /* ADS1115  @ +/- 0.256V gain (16-bit results) */
   results = ads.readADC_Differential_0_1();  
    
  //Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");
   float scale =  2.F; /* PSI/mV*/
   
   Serial.print(results*multiplier*scale);
   
   Serial.print(" ");
   
   Serial.print(digitalRead(SOL));
   
   Serial.print(" ");
      
   Serial.println(millis());
   
}

void FlopSOL()
{
   digitalWrite(SOL, !digitalRead(SOL));   // Toggle Solenoid 
   delay(5); // debounce
}
