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
  
  Modified by Dave Petrillo for Cooper Union ME 160 Lab
 ****************************************************/

#include <SPI.h> //Include library for SPI Communication 
#include "Adafruit_MAX31855.h" // Include library for Thermocouple Chip
#include <Wire.h> 
#include <Adafruit_ADS1015.h> //Include library for ADC

// Default connection is using software SPI

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define DO   6
#define CS   5
#define CLK  4
Adafruit_MAX31855 thermocouple(CLK, CS, DO);

#define SOL  8 // The pin number for the Solenoid valve relay
#define LED 13 // The pin number for the onboard LED

//ADC Setup
Adafruit_ADS1115 ads; 

int incomingByte = 0;   // for incoming serial data

void setup() {
  Serial.begin(115200); //Begin the communication with the PC via Serial (USB connector)
  //while (! Serial);  
  delay(500);  //Wait for the serial to initialize 
  
  pinMode(SOL, OUTPUT); // Set up the pin mode for the Solenoid relay output
  pinMode(LED, OUTPUT); // Set up the pin mode for the LED output
  digitalWrite(SOL, LOW); // Start with the solenoid relay unpowered (closed)
  digitalWrite(LED, LOW); // Start with the LED off
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  // We chose the highest gain because our signal is only 0-50mv, differential 
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  ads.setGain(GAIN_SIXTEEN);       // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin(); // Start up the ADC chip
  
}

void loop() {

  // Read and hanldle errors from the thermocouple chip, print the results 
   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     //Serial.println("Something wrong with thermocouple!");
    Serial.print(0); // Let's just print a '0' instead
   } else {
     Serial.print(c); // If everything is working, print out the temp in C
   }
   
   Serial.print(" "); // Print a space 
   
   int16_t results; // Initialize a variable for the results from the ADC
   float multiplier = 0.0078125F; /* This is the gain we selected for the ADS1115  @ +/- 0.256V gain (16-bit results) */
   results = ads.readADC_Differential_0_1();  // This reads the differential voltage between pin 0 and pin 1 of the ADC
    
   float scale =  2.F; /* This variable converts millivolts to PSI (PSI/mV)*/
   
   Serial.print(results*multiplier*scale); // Print out the pressure in PSI
   
   Serial.print(" "); // Print a space
   
   Serial.print(digitalRead(SOL)); // Print out the status of the Solinoid valve relay
   
   Serial.print(" "); // Print out a space
      
   Serial.println(millis()/1000.); // Print out the time in seconds since the micro has turned on
   
          if (Serial.available() > 0) { // If anything comes over the serial at all, flop the solenoid
                // read the incoming byte:
                incomingByte = Serial.read();
                FlopSOL2();
        }
}

void FlopSOL2() // This function switches the state of the solenoid valve
{
   digitalWrite(SOL, !digitalRead(SOL));   // Toggle the solenoid output pin
   digitalWrite(LED, digitalRead(SOL));   // Make the LED match the solenoid output
}
