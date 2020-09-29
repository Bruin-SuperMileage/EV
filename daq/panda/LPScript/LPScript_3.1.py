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
inputs_dict={
    'Cur' : -1,'Vlt' : -1,'Thr' : -1,'Pwr' : -1,
    'Spd' : -1,'Lng' : -1,'Lat' : -1,'Alt' : -1,'Tem' : -1,
    'GyX' : -1,'GyY' : -1,'GyZ' : -1,'AcX' : -1,'AcY' : -1,'AcZ' : -1,'MaX' : -1,'MaY' : -1,'MaZ' : -1,
    'Pit' : -1,'Rol' : -1,'Hea' : -1,'Rpm' : -1,
    }

#Begin listening to a device on the specified port (Windows)
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 0.1)

#Get the new trial number
trialName = db.child("Latest Trial").get() #trial name naming
trialName = trialName.val().split()
num = int(trialName[1]) + 1
trialName = trialName[0] + " " + (str(num))

#Account for 1600 ms delay in Arduino connection
sleep(1.6)

while(True):
  
  #Read in from the serial. Timeout if nothing is available
  text = ser.readline().decode() #read in one data string

  #Setting the time for each trial
  now = datetime.now() #set time
  timeName = now.strftime("%H:%M:%S:%f") [:-3] #set current time

  numValues = 22; #expected number of data inputs
  j = 0 #iterating variable for traversing data string
  for i in range (0, numValues):
    prefix = text[j:j+3] #KEY
    data = text[j+4:j+6] #VALUE
    inputs_dict[prefix] = float(data) #may fail on first run, simply re-run
    j+=6 #assumes 2 digit data values

  #push collected data to database
  db.child(trialName).child(timeName).update({
  "gps": 
      {"latitude": inputs_dict['Lat'],
      "longitude": inputs_dict['Lng']},
  "joulemeter": 
      {"current": inputs_dict['Cur'],
      "power": inputs_dict['Pwr'],
      "voltage": inputs_dict['Vlt']},
  "gyroscope":
      {"GyX": inputs_dict['GyX'],
      "GyY": inputs_dict['GyY'],
      "GyZ": inputs_dict['GyZ'],
      "heading": inputs_dict['Hea'],
      "pitch": inputs_dict['Pit'],
      "roll": inputs_dict['Rol']},
  "environment":
      {"altitude": inputs_dict['Alt'],
      "temperature": inputs_dict['Tem']},
  "hall-effect":
      {"rpm": inputs_dict['Rpm'],
      "throttle": inputs_dict['Thr'],
      "speed": inputs_dict['Spd']},
  "accelerometer":
      {"acceleration x": inputs_dict['AcX'],
      "acceleration y": inputs_dict['AcY'],
      "acceleration z": inputs_dict['AcZ']},
  "magnetometer":
      {"MagX": inputs_dict['MaX'],
      "MagY": inputs_dict['MaY'],
      "MagZ": inputs_dict['MaZ']},
  })

  #Updates trial information only after successful push
  db.update(
  {"Latest Trial": trialName,
  "Latest Time": timeName,
  "Running": "True"})

  num_runs += 1


#Pairs with daqTest.ino

#takes approx 450-630 ms per push, excluding outliers
#get new trial number takes approx 900 ms

#Pyrebase4 Library
#https://github.com/nhorvath/Pyrebase4