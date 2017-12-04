import serial
import time

time.sleep(3)

ser = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)

while 1:

    arduinoData = ser.readline().decode('ascii')
    print(arduinoData)
    
    



    
