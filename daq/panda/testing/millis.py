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
while(n<50):
    #Read in from the serial. Timeout if nothing is available
    text = ser.readline().decode()
    print("B")
    print(milliseconds() - start)
    print(text) 

    #Print out the text
    text = ser.readline().decode()
    print("C")
    print(milliseconds() - start)
    print(text)

    text = ser.readline().decode()
    print("D")
    print(milliseconds() - start)
    print(text) 

    text = ser.readline().decode()
    print("E")
    print(milliseconds() - start)
    print(text)

    text = ser.readline().decode()
    print("F")
    print(milliseconds() - start)
    print(text) 

    text = ser.readline().decode()
    print("G")
    print(milliseconds() - start)
    print(text) 

    n += 1
    #print('\n')

#This code demonstrates the time taken per readline: approx 8-13 ms each
#Ultimately comes to about 57 ms for the set
#Pairs with ardmil1
