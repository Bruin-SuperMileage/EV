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

newCurrent = -1 #default values
newVolt = -1
newLat = -1
newLong = -1
newSpeed = -1
newRPM = -1
newAltitude = -1
newTemp = -1
newGyroX = -1
newGyroY = -1
newGyroZ = -1
newAcX = -1
newAcY = -1
newAcZ = -1
newMagX = -1
newMagY = -1
newMagZ = -1
newPitch = -1
newRoll = -1
newHeading = -1
newThrottle = -1

file1 = open('text.txt', 'w')

joulemeterStatements = 4 #number of statements from joulemeter
otherNanoStatements = 18 #number of statements from everything else

now = datetime.now() #set time
timeName = now.strftime("%H:%M:%S") #set initial time

while (True):
  joulemeter = serial.Serial('/dev/ttyUSB0', baudrate = 9600, timeout = 1) #joulemeter Arduino
  otherNano = serial.Serial('/dev/ttyUSB1', baudrate = 9600, timeout = 1) #everything else Arduino

  now = datetime.now() #set time
  current_time = now.strftime("%H:%M:%S") #set current time   
  previousTime = timeName
  timeName = current_time
  lapNumber = db.child("Lap").get() #fetch lap number
  lapNumber = lapNumber.val()
  lapRunning = db.child("Running").get() #fetch running state
  lapRunning = lapRunning.val()

  for x in range (0, joulemeterStatements): #read joulemeter statements
    joulemeterInput = joulemeter.readline().decode('ascii')
    joulemeterInputPrefix = joulemeterInput[0:3]
    if (joulemeterInputPrefix == "Cur"):
      newCurrent = float(joulemeterInput[5:-2])
    if (joulemeterInputPrefix == "Vlt"):
      newVolt = float(joulemeterInput[5:-2])
    if (joulemeterInputPrefix == "Thr"):
      newThrottle = float(joulemeterInput[5:-2])

  newPower = newCurrent*newVolt

  for x in range (0, otherNanoStatements): #read otherNano statements
    otherNanoInput = otherNano.readline().decode('ascii')  
    otherNanoPrefix = otherNanoInput[0:3]
    if (otherNanoPrefix == "Spd"):
      newSpeed = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Lng"):
      newLong = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Lat"):
      newLat = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Alt"):
      newAltitude = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Tem"):
      newTemp = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "GyX"):
      newGyroX = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "GyY"):
      newGyroY = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "GyZ"):
      newGyroZ = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "AcX"):
      newAcX = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "AcY"):
      newAcY = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "AcZ"):
      newAcZ = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "MaX"):
      newMagX = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "MaY"):
      newMagY = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "MaZ"):
      newMagZ = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Pit"):
      newPitch = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Rol"):
      newRoll = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Hea"):
      newHeading = float(otherNanoInput[5:-2])
    if (otherNanoPrefix == "Rpm"):
      newRPM = float(otherNanoInput[5:-2])

  s = "TRIALNAME"
  file1.write(s)
  file1.write(str(trialName))
  file1.write("TIMENAME")
  file1.write(str(timeName))
  file1.write("PREVIOUSTIME")
  file1.write(str(previousTime))
  file1.write("NEWLAT")
  file1.write(str(newLat))
  file1.write("NEWLONG")
  file1.write(str(newLong))
  file1.write("NEWCURRENT")
  file1.write(str(newCurrent))
  file1.write("NEWVOLT")
  file1.write(str(newVolt))
  file1.write("NEWPOWER")
  file1.write(str(newPower))
  file1.write("NEWRPM")
  file1.write(str(newRPM))
  file1.write("NEWSPEED")
  file1.write(str(newSpeed))
  file1.write('\n')
  file1.write('\n')
  file1.write('\n')

  db.update(
    {"Latest Trial": trialName,
    "Latest Time": timeName, 
    "Previous Time": previousTime})

#  db.child(trialName).child(timeName).child("battery").update(
#   {"amp": 0,
#    "remaining": 0,
#    "temp": 0,
#    "volt": 0})

#  db.child(trialName).child(timeName).child("driver").update(
#    {"image": "./images/Caroline.jpg",
#    "message": "I Believe In You!!!",
#    "name": "Caroline",
#    "phone": "999-999-999",
#    "social": "@CarolineDriver"})

  db.child(trialName).child(timeName).child("gps").update(
    {"lat": newLat,
    "long": newLong})

  db.child(trialName).child(timeName).child("joulemeter").update(
    {"current": newCurrent,
    #"avg": 0,
    "power": newPower,
    #"peak": 0,
    "voltage": newVolt})

  db.child(trialName).child(timeName).child("gyroscope").update(
    {"GyX": newGyroX,
    "GyY": newGyroY,
    "GyZ": newGyroZ,
    "heading": newHeading,
    "pitch": newPitch,
    "roll": newRoll})

  db.child(trialName).child(timeName).child("environment").update(
    {"altitude": newAltitude,
    "temperature": newTemp})
  
  db.child(trialName).child(timeName).child("hall-effect").update(
    {"rpm": newRPM,
    "throttle": newThrottle,
    "speed": newSpeed})

#  db.child(trialName).child(timeName).child("lap").update(
#    {"current": lapNumber,
#    "fastest": 0,
#    "number": 0,
#    "remaining": 0,
#    "slowest": 0,
#    "total": 0,
#    "running": lapRunning})

#  db.child(trialName).child(timeName).child("motor").update(
#    {"bhp": 0,
#    "temp": 0,
#    "volt": 0})

  db.child(trialName).child(timeName).child("accelerometer").update(
    {"acceleration x": newAcX,
    "acceleration y": newAcY,
    "acceleration z": newAcZ})
    #"avg": 0,
    #"rpm": newRPM,
    #"speed": newSpeed,
    #"throttle": newThrottle})

#  db.child(trialName).child(timeName).child("track").update(
#    {"name": "Parking Garage",
#    "trial": 1,
#    "temp": newTemp})

  db.child(trialName).child(timeName).child("magenetometer").update(
    {"MagX": newMagX,
    "MagY": newMagY,
    "MagZ": newMagZ})
    #"Pitch": newPitch,
    #"Roll": newRoll,
    #"Heading": newHeading})
