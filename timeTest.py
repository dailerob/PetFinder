#code to test timing capabilities of the arduino
#Roberto Dailey 
#12-1-2017


from nanpy import (ArduinoApi, SerialManager)
from time import sleep

try:
    connection = SerialManager()
    a = ArduinoApi(connection = connection)
except:
    print("You have failed to connect to Arduino")

#wait for a bit
sleep(5)

startTime = int(a.millis())
print(str(test))

for i in range(1:5):
    a.delay(1000)
    currentTime  = int(a.millis)-startTime

    print(" ")
    print("time at iteration "+ str(i)+": " + str(currentTime))