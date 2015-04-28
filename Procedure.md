# Lab Procedure

## Introduction:

In this lab you will use an Arduino based data acquisition system to measure dynamic pressure and temperature profiles of a pressure vessel during venting. You will be required to download the code from github, load it to the arduino, hook up the sensors and operate the pressure vessel to record measurements for 4 different tests. 

## Software: 

The required software packages that have already been installed on computer LL224-1 in the SAE lab are: 
- Arduino IDE
- Python 2.7
- Numpy
- Matplotlib

Each time you run this lab, start by downloading this repository from github using the "Download ZIP" button on the homepage of this repository. This will ensure you have the most recent version of this lab. 

Download the lab to a known directory such as: 'C:\Users\student\downloads' 

Open the Arduino IDE located in: 'C:\Users\student\Downloads\arduino-1.6.3'

Load the ME160.ino file onto the Arduino IDE. Be sure to select the correct board, port and programmer in the Arduino IDE settings. 

Verify the code and then download it to the physical Arduino board using the Check mark symbol and the Upload button in the Arduino IDE

The libraries that are used in the arduino sketch are listed on the main github readme and must be downloaded and installed to the correct location (usually 'user\Documents\Arduino' Note that the IDE may have to be restarted to recognize newly added libraries. 

Open a command prompt (Start Menu > Search > 'cmd.exe') and navigate to the folder containing 'ReadData.py' in the main github directory. You can change directories using the 'cd ' command. Use the following commands to check that Python and the other required packages are properly installed. 

```python 
> python
```
Once inside the python interpreter, check that the packages import without error:

```python 
>> import numpy
>> import matplotlib
```
Exit the interpreter using quit()

```python 
>> quit()
```

In order to use the data acquisition script, the following use a command similar to: 

```python 
> python ReadData.py --port COM5
```

## Hardware:

Use the following procedure to capture pressure venting data for 4 different nozzle sizes: 

- Attach make the electrical connections to the pressure vessel for the power supply, solenoid, thermocouple, and pressure transducer according to the wiring diagram photo. 
![Diagram](https://github.com/dpetrillo740/ME160/blob/master/ME160%20Drawing.png?raw=true)
- Connect the chosen nozzle size
- Fill the pressure vessel with air using the green hose attachment in the center of the SAE lab. Fill to the maximum pressure available in the lab, do not exceed 80PSI. Wait a few minutes for the temperature inside the vessel to stabilize. 
- Start the python ReadData.py script to begin reading and recording data from the setup. Verify that temperature (blue) and pressure(green) match expected values (Degrees C and PSI)
- The on board red LED will indicate the status of the relay to power the solenoid, off is closed and red is open.
- Warn your fellow lab mates and begin venting by clicking the 'Open/Close solenoid valve' button 
- Wait for the temperature to stabilize after the pressure has fully vented to exit the test by exiting out of the graph window. - Review your data using the .CSV file that has been created in the main github directory.  
- Save this file noting the nozzle size used
- Repeat for all 4 nozzles

If you have any issues while conducting this lab, please make a new issue using the (!) button at the right. You must be logged into github in order to do so.
