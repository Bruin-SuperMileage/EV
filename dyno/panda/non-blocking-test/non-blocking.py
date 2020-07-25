import serial
from time import time

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('COM5', baudrate = 9600, timeout = 0.01)

#Define function to get current time in milliseconds
milliseconds = lambda: int(time() * 1000)

#Get current time - START NOW
start = milliseconds()

#See how much time has elapsed since START NOW
print("A")
print(milliseconds() - start)

while(True):
    #Read in from the serial. Timeout if nothing is available
    text = ser.readline().decode()
    print("B")
    print(milliseconds() - start) 

    #Print out the text
    print("C")
    print(text)
    print(milliseconds() - start) 
