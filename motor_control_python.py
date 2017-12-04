import serial
import time
time.sleep(3)

#input_serial = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)
output_serial = serial.Serial('/dev/cu.usbmodem1411', baudrate = 19200, timeout = 1)

direction = ''
while direction != 'stop':
	print("Enter a direction")
	print("[Forward = F, Reverse = B, Left = L, Right = R]")
	direction = input()
	output_serial.write(direction.encode())
	if direction == 'L' or direction == 'R':
		print("How much turn?")
		amount = input()
		output_serial.write(amount.encode())
