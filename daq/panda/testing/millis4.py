import serial
from time import time

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 0.1)

#Define function to get current time in milliseconds
milliseconds = lambda: int(time() * 1000)

#Get current time - START NOW
start = milliseconds()

#See how much time has elapsed since START NOW
print("Start here:")
print(milliseconds() - start)

n = 0
while(n<50):
    #Read in from the serial. Timeout if nothing is available
    text = ser.readline().decode()
    print(milliseconds() - start)
    j = 0
    for i in range (0, 22):
    	print(text[j:j+6])
    	j+=6
    n += 1

#Building on millis 3 by printing individual values
#Testing readline speed for single string:
#takes approx 140 ms for 22 unique data values
#shaves almost 40 ms off of millis1str time (180 ms)

#Pairs with ardmil4