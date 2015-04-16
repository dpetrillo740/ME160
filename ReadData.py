"""
Display analog data from Arduino using Python (matplotlib)

Adapted from code by:
Author: Mahesh Venkitachalam
Website: electronut.in

Modified by Dave Petrillo for Cooper Union
"""

import sys, serial, argparse
import numpy as np
from time import sleep
from collections import deque
import csv
import datetime

import matplotlib.pyplot as plt 
import matplotlib.animation as animation

    
# plot class
class AnalogPlot:
  # constr
  def __init__(self, strPort, maxLen):
      now = datetime.datetime.now()
      datalog = open('Experiment Data '+ now.strftime("%Y-%m-%d %H:%M") +'.csv', 'wb')
      dl = csv.writer(datalog)
      dl.writerow(['Data Logged From Pressure Experiment'])
      dl.writerow(['Temperature (C)', 'Pressure', 'Valve State', 'Time (mS)'])
      # open serial port
      self.ser = serial.Serial(strPort, 115200)

      self.ax = deque([0.0]*maxLen)
      self.ay = deque([0.0]*maxLen)
      self.maxLen = maxLen
      self.dl = dl.writerow

  # add to buffer
  def addToBuf(self, buf, val):
      if len(buf) < self.maxLen:
          buf.append(val)
      else:
          buf.pop()
          buf.appendleft(val)

  # add data
  def add(self, data):
      # assert(len(data) == 2)
      self.addToBuf(self.ax, data[0])
      self.addToBuf(self.ay, data[1])

  # update plot
  def update(self, frameNum, a0, a1):

      try:
          line = self.ser.readline()
          data = [float(val) for val in line.split()]
          self.dl(data)
          # print data
          #if(len(data) == 2):
          self.add(data)
          a0.set_data(range(self.maxLen), self.ax)
          a1.set_data(range(self.maxLen), self.ay)
      except KeyboardInterrupt:
          print('exiting')
      
      return a0, 

  # clean up
  def close(self):
      # close serial
      self.ser.flush()
      self.ser.close()    

# main() function
def main():
  # create parser
  parser = argparse.ArgumentParser(description="LDR serial")
  # add expected arguments
  parser.add_argument('--port', dest='port', required=True)

  # parse args
  args = parser.parse_args()
  
  #strPort = '/dev/tty.usbserial-A7006Yqh'
  strPort = args.port

  print('reading from serial port %s...' % strPort)

  # plot parameters
  analogPlot = AnalogPlot(strPort, 10000)

  print('plotting data...')

  # set up animation
  fig = plt.figure()
  ax = plt.axes(xlim=(0, 1000), ylim=(-5, 100))
  a0, = ax.plot([], [])
  a1, = ax.plot([], [])
  anim = animation.FuncAnimation(fig, analogPlot.update, 
                                 fargs=(a0, a1), 
                                 interval=10)

  # show plot
  plt.show()
  
  # clean up
  analogPlot.close()

  print('exiting.')
  

# call main
if __name__ == '__main__':
  main()
