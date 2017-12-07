##main file for running python code within our project. 
#serial communication library
import serial


##Set up Serial communication with the Lidar system 
sleep(2)
input_serial = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)
sleep(2)
from time import sleep


print("Start command loop [c] or read serial output [r]")
startResponse = input
	if(command == "r"):
		readSerial()


import RPi.GPIO as IO          #calling header file which helps us use GPIO’s of PI

##set up python control of Lidar motor
IO.setwarnings(False)           #do not show any warnings
IO.setmode (IO.BCM)         #we are programming the GPIO by BCM pin numbers. (PIN35 as ‘GPIO19’)

IO.setup(19,IO.OUT)           # initialize GPIO19 as an output.
IO.setup(16,IO.OUT)
IO.setup(20,IO.OUT)

IO.output(16,1)
IO.output(20,0)
p = IO.PWM(19,500000)          #GPIO19 as PWM output, with 50KHz frequency

p.start(0)                              #generate PWM signal with 0% duty cycle
##end of setup for python control of Lidar motor controller.##

#start the loop 

direction = ''
while direction != 'stop':
	######################################################## MAIN LOOP FOR CONTROL ############################################
	##logic for sending commands to the raspberry pi
	sendMessage = ''
	print("Enter [direction,time] to move forward/backwards or [turn direction,degrees]")
	print("[Left = L, Right = R]")
	print("[amount is in seconds]")

	sendMessage = input()
	direction = sendMessage[0]#get the first character of the inputed string 
	output_serial.write(direction.encode())


	



	######################################################## MAIN LOOP FOR CONTROL ############################################



###any necissary closes. 
disableLidar() 




def enableLidar():
	p.ChangeDutyCycle(50)

def disableLidar():
	p.ChangeDutyCycle(0)

def readSerial(): 
	while(1):
		arduinoData = ser.readline().decode().strip().split(",")
		print('arduino Data' + str(arduinoData))

