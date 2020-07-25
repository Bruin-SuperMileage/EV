import pyrebase
import time
import serial
from datetime import datetime

config = {
    "apiKey": "AIzaSyAnFTWZTgWEugKOSUM6WY_NkxrPzRzn6dU",
    "authDomain": "bruin-racing.firebaseapp.com",
    "databaseURL": "https://bruin-racing.firebaseio.com",
    "projectId": "bruin-racing",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

trialName = db.child("Latest Trial").get()
trialName = trialName.val().split()
num = int(trialName[1]) + 1
trialName = trialName[0] + " " + (str(num))

now = datetime.now()
current_timet_time = now.strftime("%H:%M:%S")
timeName = current_time

db.update(
    {"Latest Trial": trialName,
    "Latest Time": timeName})

