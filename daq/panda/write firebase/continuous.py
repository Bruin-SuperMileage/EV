#the purpose of this file is to write code that continuously increments the values in firebase every 2 seconds

#this file works completely perfectly
#do not mess up this file

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

while (runSpeed == True):
     db.child("speed").update({"0": newSpeed})
     time.sleep(2)
     newSpeed = newSpeed + 1
     print(newSpeed)
