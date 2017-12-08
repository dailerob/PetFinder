##main file for running python code within our project. 
#serial communication library
import serial


##Set up Serial communication with the Lidar system 
sleep(2)
input_serial = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)
sleep(2)
from time import sleep

################################check if we want to run in a debug mode where we only read the serial output########
print("Start command loop [c] or read serial output [r]")
startResponse = input
	if(command == "r"):
		readSerial()
################################check if we want to run in a debug mode where we only read the serial output########



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

controlOn = True #this will be a boolean telling us weather we can stop to ask for a new command
lidarData = 0
lidarTime = 0
motor1Pos = 0
motor2Pos = 0
motorTimePos = 0



while direction != 'stop':
	######################################################## MAIN LOOP FOR CONTROL ############################################

	if controlOn :
		##logic for sending commands to the raspberry pi
		sendMessage = ''
		print("Enter [direction,time] to move forward/backwards or [turn direction,degrees]")
		print("[Left = L, Right = R]")
		print("[amount is in seconds]")

		sendMessage = input()
		direction = sendMessage[0]#get the first character of the inputed string 
		output_serial.write(direction.encode())
		startTime = lidarData


	#######read###############
	arduinoData = ser.readline().decode().strip()
	if arduinoData[0] = "S" :
		arduinoData = arduinoData.split(",")
		lidarData = arduinoData[1]
		lidarTime = arduinoData[2]
		motor1Pos = arduinoData[3]
		motor2Pos = arduinoData[4]
		motorTimePos = arduinoData[5]
	#######read###############

	if(lidarTime-Start)



	######################################################## MAIN LOOP FOR CONTROL ############################################



###any necissary closes. 
disableLidar() 




def enableLidar():
	for x in range (50):                          #execute loop for 50 times, x being incremented from 0 to 49.
		p.ChangeDutyCycle(x)               #change duty cycle for varying the brightness of LED.
		time.sleep(0.05) 
	p.ChangeDutyCycle(50)

def disableLidar():
	p.ChangeDutyCycle(0)

def readSerial(): 
	while(1):
		arduinoData = ser.readline().decode().strip().split(",")
		print('arduino Data' + str(arduinoData))

