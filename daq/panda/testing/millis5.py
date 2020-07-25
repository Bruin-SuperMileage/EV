import serial
import pyrebase
from time import time

config = { #firebase authentification
    "apiKey": "AIzaSyDEfkwr7Zl5WucXFluMxB8VIlngUnp7aDM",
    "authDomain": "smv-daq.firebaseapp.com",
    "databaseURL": "https://smv-daq.firebaseio.com",
    "projectId": "smv-daq",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 0.1)

#Define function to get current time in milliseconds
milliseconds = lambda: int(time() * 1000)

#Get current time - START NOW
start = milliseconds()

#See how much time has elapsed since START NOW
print("Start here:")
print(milliseconds() - start)

numValues = 22;
n = 0
while(n<50):
    #Read in from the serial. Timeout if nothing is available
    text = ser.readline().decode()
    print(milliseconds() - start)
    j = 0 #iterating variable
    for i in range (0, numValues):
      data = text[j:j+6]
      db.child("data").push(data)
      j+=6
    n += 1


#Pairs with ardmil5
#non dictionary variation: 6000 ms per push
#https://github.com/nhorvath/Pyrebase4