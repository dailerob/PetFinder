#code to test timing capabilities of the arduino
#Roberto Dailey 
#12-1-2017

import serial 
from time import sleep


ser = serial.Serial('COM5', baudrate = 9600, timeout = 1)
#wait for a bit
sleep(5)

for i in range(5000):
	arduinoData = ser.readline().decode().strip().split(",")
	testInfo = int(arduinoData[0])
	print('arduino Data' + str(arduinoData))
	print(str(testInfo))
	
