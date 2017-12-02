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

test = a.millis()
print(str(test))
