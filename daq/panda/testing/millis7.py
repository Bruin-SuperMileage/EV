import serial
import pyrebase
from time import time, sleep
from datetime import datetime

config = { #firebase authentification
    "apiKey": "AIzaSyDEfkwr7Zl5WucXFluMxB8VIlngUnp7aDM",
    "authDomain": "smv-daq.firebaseapp.com",
    "databaseURL": "https://smv-daq.firebaseio.com",
    "projectId": "smv-daq",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

#declare the dictionary to store all input data
my_dict={
    'Pot' : -1,
    'Cur' : -1,'Vlt' : -1,'Thr' : -1,'Pwr' : -1,
    'Spd' : -1,'Lng' : -1,'Lat' : -1,'Alt' : -1,'Tem' : -1,
    'GyX' : -1,'GyY' : -1,'GyZ' : -1,'AcX' : -1,'AcY' : -1,'AcZ' : -1,'MaX' : -1,'MaY' : -1,'MaZ' : -1,
    'Pit' : -1,'Rol' : -1,'Hea' : -1,'Rpm' : -1,
    }

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 0.1)

#Define function to get current time in milliseconds
milliseconds = lambda: int(time() * 1000)

#Get current time - START NOW
start = milliseconds()

#Get the new trial number
trialName = db.child("Latest Trial").get() #trial name naming
trialName = trialName.val().split()
num = int(trialName[1]) + 1
trialName = trialName[0] + " " + (str(num))

#See how much time has elapsed since START NOW
print("Start here:")
print(milliseconds() - start)

#Account for 1600 ms delay in Arduino connection
sleep(1.6)

numValues = 23
inputLength = 7
n = 0 #test iterator
while(n<50):
  #Read in from the serial. Timeout if nothing is available
  text = ser.readline().decode() #read in one data string
  print(milliseconds() - start)

  #Setting the time for each trial
  now = datetime.now() #set time
  timeName = now.strftime("%H:%M:%S.%f") [:-3] #set current time

  j = 0 #iterating variable for traversing data string
  for i in range (0, numValues):
    prefix = text[j:j+3] #KEY
    data = text[j+4:j+7] #VALUE: 3 digits
    my_dict[prefix] = float(data)
    j+=inputLength

  db.update({"Latest Trial": trialName})

  db.child(trialName).child(timeName).update({
  "potentiometer": 
      {"potential": my_dict['Pot']},
  "gps": 
      {"lat": my_dict['Lat'],
      "long": my_dict['Lng']},
  "joulemeter": 
      {"current": my_dict['Cur'],
      "power": my_dict['Pwr'],
      "voltage": my_dict['Vlt']},
  "gyroscope":
      {"GyX": my_dict['GyX'],
      "GyY": my_dict['GyY'],
      "GyZ": my_dict['GyZ'],
      "heading": my_dict['Hea'],
      "pitch": my_dict['Pit'],
      "roll": my_dict['Rol']},
  "environment":
      {"altitude": my_dict['Alt'],
      "temperature": my_dict['Tem']},
  "hall-effect":
      {"rpm": my_dict['Rpm'],
      "throttle": my_dict['Thr'],
      "speed": my_dict['Spd']},
  "accelerometer":
      {"acceleration x": my_dict['AcX'],
      "acceleration y": my_dict['AcY'],
      "acceleration z": my_dict['AcZ']},
  "magenetometer":
      {"MagX": my_dict['MaX'],
      "MagY": my_dict['MaY'],
      "MagZ": my_dict['MaZ']}
  })

  n += 1


#Pairs with ardmil7
#which uses a potentiometer to measure delays due to sensor inputs

#non dictionary variation: 6000 ms per push
#with dictionary: 460-630 ms per push, excluding outliers
#with potentiometer attached, averaging 460-560 ms per push

#get new trial number takes approx 900 ms

#suggestion: implement !Serial to avoid use of sleep

#Pyrebase4 Library
#https://github.com/nhorvath/Pyrebase4