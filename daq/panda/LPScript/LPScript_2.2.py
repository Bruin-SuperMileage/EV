import pyrebase
import time
import serial
from datetime import datetime

config = { #firebase authentification
    "apiKey": "AIzaSyAnFTWZTgWEugKOSUM6WY_NkxrPzRzn6dU",
    "authDomain": "bruin-racing.firebaseapp.com",
    "databaseURL": "https://bruin-racing.firebaseio.com",
    "projectId": "bruin-racing",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

trialName = db.child("Latest Trial").get() #trial name naming
trialName = trialName.val().split()
num = int(trialName[1]) + 1

trialName = trialName[0] + " " + (str(num))

#declare the dictionary to store all input data
my_dict={
    'Cur' : -1,'Vlt' : -1,'Thr' : -1,'Pwr' : -1,
    'Spd' : -1,'Lng' : -1,'Lat' : -1,'Alt' : -1,'Tem' : -1,
    'GyX' : -1,'GyY' : -1,'GyZ' : -1,'AcX' : -1,'AcY' : -1,'AcZ' : -1,'MaX' : -1,'MaY' : -1,'MaZ' : -1,
    'Pit' : -1,'Rol' : -1,'Hea' : -1,'Rpm' : -1,
    }

file1 = open('text.txt', 'w')

joulemeterStatements = 4 #number of statements from joulemeter
otherNanoStatements = 18 #number of statements from everything else

now = datetime.now() #set time
timeName = now.strftime("%H:%M:%S") #set initial time

while (True):
  joulemeter = serial.Serial('/dev/ttyUSB0', baudrate = 9600, timeout = 0.01) #joulemeter Arduino
  otherNano = serial.Serial('/dev/ttyUSB1', baudrate = 9600, timeout = 0.01) #everything else Arduino

  now = datetime.now() #set time
  current_time = now.strftime("%H:%M:%S") #set current time   
  previousTime = timeName
  timeName = current_time
  lapNumber = db.child("Lap").get() #fetch lap number
  lapNumber = lapNumber.val()
  lapRunning = db.child("Running").get() #fetch running state
  lapRunning = lapRunning.val()

  for x in range (0, joulemeterStatements): #read joulemeter statements
    joulemeterInput = joulemeter.readline().decode('ascii') #read one statement
    joulemeterInputPrefix = joulemeterInput[0:3] #parse the statement for the first three characters (KEY)
    my_dict[joulemeterInputPrefix] = float(joulemeterInput[5:-2]) #assign VALUE to KEY in dictionary

  for x in range (0, otherNanoStatements): #read otherNano statements
    otherNanoInput = otherNano.readline().decode('ascii') #read one statement
    otherNanoPrefix = otherNanoInput[0:3] #parse the statement for the first three characters (KEY)
    my_dict[otherNanoPrefix] = float(otherNanoInput[5:-2]) #assign VALUE TO KEY in dictionary

  db.update(
    {"Latest Trial": trialName,
    "Latest Time": timeName, 
    "Previous Time": previousTime})

  db.child(trialName).child(timeName).child("gps").update(
    {"lat": my_dict['Lat'],
    "long": my_dict['Lng']})

  db.child(trialName).child(timeName).child("joulemeter").update(
    {"current": my_dict['Cur'],
    "power": my_dict['Pwr'],
    "voltage": my_dict['Vlt']})

  db.child(trialName).child(timeName).child("gyroscope").update(
    {"GyX": my_dict['GyX'],
    "GyY": my_dict['GyY'],
    "GyZ": my_dict['GyZ'],
    "heading": my_dict['Hea'],
    "pitch": my_dict['Pit'],
    "roll": my_dict['Rol']})

  db.child(trialName).child(timeName).child("environment").update(
    {"altitude": my_dict['Alt'],
    "temperature": my_dict['Tem']})
  
  db.child(trialName).child(timeName).child("hall-effect").update(
    {"rpm": my_dict['Rpm'],
    "throttle": my_dict['Thr'],
    "speed": my_dict['Spd']})

#  db.child(trialName).child(timeName).child("lap").update(
#    {"current": lapNumber,
#    "fastest": 0,
#    "number": 0,
#    "remaining": 0,
#    "slowest": 0,
#    "total": 0,
#    "running": lapRunning})

  db.child(trialName).child(timeName).child("accelerometer").update(
    {"acceleration x": my_dict['AcX'],
    "acceleration y": my_dict['AcY'],
    "acceleration z": my_dict['AcZ']})

  db.child(trialName).child(timeName).child("magenetometer").update(
    {"MagX": my_dict['MaX'],
    "MagY": my_dict['MaY'],
    "MagZ": my_dict['MaZ']})
