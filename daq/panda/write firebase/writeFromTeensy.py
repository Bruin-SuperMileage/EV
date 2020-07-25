import serial
import pyrebase
import time

config = {
    "apiKey": "AIzaSyAnFTWZTgWEugKOSUM6WY_NkxrPzRzn6dU",
    "authDomain": "bruin-racing.firebaseapp.com",
    "databaseURL": "https://bruin-racing.firebaseio.com",
    "projectId": "bruin-racing",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()
runSpeed = True
newSpeed = 0

s = serial.Serial('COM6', baudrate = 9600, timeout = 1)

while (runSpeed == True):
     res = s.readline().decode('ascii')
     print(res)

     newSpeed = res
     db.child(trialName).child(timeName).child("speed").update(
                            {"acceleration": 0,
                            "avg": 0,
                            "brake": 0,
                            "speed": newSpeed,
                            "throttle": 0})
