import RPi.GPIO as IO          #calling header file which helps us use GPIO’s of PI
import time                            #calling time to provide delays in program
IO.setwarnings(False)           #do not show any warnings
IO.setmode (IO.BCM)         #we are programming the GPIO by BCM pin numbers. (PIN35 as ‘GPIO19’)

IO.setup(17,IO.OUT)           # initialize GPIO19 as an output.
IO.setup(27,IO.OUT)
IO.setup(22,IO.OUT)

IO.output(27,1)
IO.output(22,0)
p = IO.PWM(17,1000)          #GPIO19 as PWM output, with 50KHz frequency

p.start(0)                              #generate PWM signal with 0% duty cycle
y = 0
print("right before while loop")
for y in range (4):                               #execute loop forever
        print(y)
	#for x in range (50):                          #execute loop for 50 times, x being incremented from 0 to 49.
	#	p.ChangeDutyCycle(x)               #change duty cycle for varying the brightness of LED.
	#	time.sleep(0.1)    
		                       #sleep for 100m second
	#for x in range (50):                         #execute loop for 50 times, x being incremented from 0 to 49.
	#	p.ChangeDutyCycle(50-x)        #change duty cycle for changing the brightness of LED.
	#	time.sleep(0.1) #sleep for 100m second
        p.ChangeDutyCycle(30)
        time.sleep(2.0)
		
p.ChangeDutyCycle(0)


