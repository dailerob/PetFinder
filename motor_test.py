#code to replicate the go forward program in
#raspberry pi


from nanpy import (ArduinoApi, SerialManager)
from time import sleep

#motor one
enA = 10
in1 = 9
in2 = 8

#motor two
enB = 5
in3 = 7
in4 = 6

try:
    connection = SerialManager()
    a = ArduinoApi(connection = connection)
except:
    print("Failed to connect to Arduino")

#setup the pin modes as if they were in the Arduino IDE
a.pinMode(enA, a.OUTPUT)
a.pinMode(enB, a.OUTPUT)
a.pinMode(in1, a.OUTPUT)
a.pinMode(in2, a.OUTPUT)
a.pinMode(in3, a.OUTPUT)
a.pinMode(in4, a.OUTPUT)

try:
    while True:
        a.digitalWrite(in1, a.HIGH)
        a.digitalWrite(in2, a.LOW)
        a.analogWrite(enA, 255)
                
        a.digitalWrite(in3, HIGH);
        a.digitalWrite(in4, a.LOW)
        a.analogWrite(enB, 255)
        a.delay(5000);
        a.analogWrite(enA, 0)
        a.analogWrite(enB, 0)
except:
    a.digitalWrite(enA, a.LOW)
    a.digitalWrite(enB, a.LOW)
    a.digitalWrite(in1, a.LOW)
    a.digitalWrite(in2, a.LOW)
    a.digitalWrite(in3, a.LOW)
    a.digitalWrite(in4, a.LOW)


