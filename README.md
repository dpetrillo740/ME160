#Pressure vessel 
A ME160 Lab for Cooper Union

Parts: 
- Adafruit Pro Trinket - 3V 12MHz: http://www.adafruit.com/product/2010
- ADS1115 16-Bit ADC - 4 Channel with Programmable Gain Amplifier: https://www.adafruit.com/products/1085
- Thermocouple Amplifier MAX31855 breakout board  http://www.adafruit.com/products/269
- FTDI Usb to serial converter

Procedure to create data acquisition board: 
Attach The two signal boards to the Pro Trinket. 
Use the following libraries to create arduino code to read sensors: 
https://github.com/adafruit/Adafruit-MAX31855-library
https://github.com/adafruit/Adafruit_ADS1X15

Use this repository to create a python script to graph and log data: 
https://gist.github.com/electronut/d5e5f68c610821e311b0
from: http://www.instructables.com/id/Plotting-real-time-data-from-Arduino-using-Python-/

