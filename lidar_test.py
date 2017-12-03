#code measure lidar response 
#raspberry pi
#Roberto Dailey

#import libraries
from nanpy import (ArduinoApi, SerialManager)
from time import sleep


#check that we can connect to the arduino
try:
    connection = SerialManager()
    a = ArduinoApi(connection = connection)
except:
    print("Failed to connect to Arduino")


#set up variables
dist = 0
strength  = 0
check = 0
i  = 0
uart = [None] * 9
HEADER = 0x59

from nanpy import SoftwareSerial

a.SoftwareSerial Serial1(2,3)

a.Serial.begin(9600)
a.Serial1.begin(115200)


while(True):
    if a.Serial1.availible():
        if a.Serial1.read()==HEADER:
            uart[0] = HEADER
            if a.Serial1.read()==HEADER:
                uart[1] = HEADER
                for i in range(2,9):
                    uart[i] = a.Serial1.read()

                #check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7]
                #if uart[8]==check and uart[8] == 0xff:
                #   dist = uart[2]+uart[3]*256
                #   print(str(dist))


