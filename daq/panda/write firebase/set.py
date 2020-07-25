#this file works completely perfectly
#do not mess up this file

import pyrebase

config = {
    "apiKey": "AIzaSyAnFTWZTgWEugKOSUM6WY_NkxrPzRzn6dU",
    "authDomain": "bruin-racing.firebaseapp.com",
    "databaseURL": "https://bruin-racing.firebaseio.com",
    "projectId": "bruin-racing",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()


jsonStuff = db.child("gps").get()
print(jsonStuff.val())

data = {
    "0": 123,
    "1": 123123123,
    "2": 1231231241231231231
}

db.child("speed").child("newSpeed").set(data)
