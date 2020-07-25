import serial
from time import time

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 0.1)

#Define function to get current time in milliseconds
milliseconds = lambda: int(time() * 1000)

#Get current time - START NOW
start = milliseconds()

#See how much time has elapsed since START NOW
print("Starts here:")
print(milliseconds() - start)

n = 0
while(n<50):
    #Read in from the serial. Timeout if nothing is available. Print text
    text = ser.readline().decode()
    print(milliseconds() - start)
    print(text) 

    n += 1

#This code demonstrates the time taken per readline: approx 8 ms each
#Ultimately comes to about 180 ms for the set of 22 readlines
#Pairs with ardmil1.5
