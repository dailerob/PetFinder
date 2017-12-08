##main file for running python code within our project. 
#serial communication library
import serial
from time import sleep


def enableLidar():
  power = 25
  for x in range (power):                          #execute loop for 50 times, x being incremented from 0 to 49.
    p.ChangeDutyCycle(x)               #change duty cycle for varying the brightness of LED.
    sleep(0.1)
  p.ChangeDutyCycle(power)

def disableLidar():
  p.ChangeDutyCycle(0)

def readSerial(): 
  while(1):
    arduinoData = input_serial.readline().decode().strip().split(",")
    print('arduino Data' + str(arduinoData))


##Set up Serial communication with the Lidar system 
sleep(2)
input_serial = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)
sleep(2)

################################check if we want to run in a debug mode where we only read the serial output########
print("Start command loop [c] or read serial output [r]")
startResponse = input()
if(startResponse == "r"):
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
p = IO.PWM(19,1000)          #GPIO19 as PWM output, with 1KHz frequency

p.start(0)                              #generate PWM signal with 0% duty cycle

##end of setup for python control of Lidar motor controller.##

#start the loop 

controlOn = True #this will be a boolean telling us weather we can stop to ask for a new command
lidarData = 0
lidarTime = 0
motor1Pos = 0
motor2Pos = 0
motorTimePos = 0

charInput = ' '
wait = 0
startTime = 0
ValuesCorrect = False

while charInput != 'stop':
  ######################################################## MAIN LOOP FOR CONTROL ############################################

  if controlOn :
    ##logic for sending commands to the raspberry pi
    sendMessage = ''
    print("Enter [direction,time] to move forward/backwards or [turn direction,degrees]")
    print("[Left = L, Right = R, Forward = F, Backwards = B]")
    print("[Enable Lidar = E, Disable Lidar = D]")

    sendMessage = input()
    charInput = sendMessage[0]#get the first character of the inputed string 
    if charInput == '' 
    if charInput == 'D':
      disableLidar()
    else:
      wait = float(sendMessage[2])#get the first character of the inputed string 
      input_serial.write(charInput.encode())
      startTime = lidarTime


  #######read###############
  try:
    arduinoData = input_serial.readline().decode().strip()
    if arduinoData[0] == "S" and arduinoData[7] == "E":
      arduinoData = arduinoData.split(",")
      lidarData = float(arduinoData[1])
      lidarTime = float(arduinoData[2])
      lidarEncoder = float(arduinoData[3])
      motor1Pos = float(arduinoData[4])
      motor2Pos = float(arduinoData[5])
      motorTimePos = float(arduinoData[6])
      ValuesCorrect = True
  
  except: 
      ValuesCorrect = False
  #######read###############

  if(lidarTime-startTime < wait*1000): 
    controlOn = False
  else:
    controlOn = True


  ######################################################## MAIN LOOP FOR CONTROL ############################################



###any necissary closes. 
disableLidar() 




'''
def calcLidar(distance, encoderValue, lidarData):
  
  numRevsBeforeStart = 6


  prevEncoder = lidarData[0] The previous Encoder Value read
  numCounts = lidarData[1] The number of counts since the encoder began counting 
  pointsPerTab = lidarData[2] The number of points counted on each tab
  currentTab = lidarData[3] The current tab index 
  Distances = lidarData[4] the Distances calculated on each tab. 
  Angles = lidarData[5] the angles for each tab

  if prevEncoder != encoderValue :
    numCounts = numCounts+1
  
  #wait for lidar to spin up
  if numcounts > numRevsBeforeStart*26:
    #use 3 revs to determine correct tabs
    if numcounts < (numRevsBeforeStart+3)*26:
      if prevEncoder != encoderValue :
        pointsPerTab[currentTab]= pointsPerTab[currentTab] + len(Distances[currentTab])
        currentTab = currentTab + 1

        Distances[]


  prevEncoder
  return (lidarData)

'''
