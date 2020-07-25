import serial
from time import time

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 0.1)

#Define function to get current time in milliseconds
milliseconds = lambda: int(time() * 1000)

#Get current time - START NOW
start = milliseconds()

#See how much time has elapsed since START NOW
print("A")
print(milliseconds() - start)

n = 0
while(n<100):
    #Read in from the serial. Timeout if nothing is available
    text = ser.readline().decode()
    print("B")
    print(milliseconds() - start)
    print(text)
    n += 1

#Testing readline speed for single string:
#takes approx 40 ms for 6 unique data values
#shaves almost 15 ms off of millis1 time, scale with number of data values

#Pairs with ardmil2