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

trialName = "Trial 1"
timeName = "12:12:31"

db.update(
    {"Latest Trial": trialName,
    "Latest Time": timeName})

db.child(trialName).child(timeName).child("battery").update(
                         {"amp": 31,
                          "remaining": 61,
                          "temp": 81,
                          "volt": 15})

db.child(trialName).child(timeName).child("driver").update(
                         {"image": "./images/Lexi.png",
                          "message": "Going for Gold",
                          "name": "Lexi",
                          "phone": "973-979-0991",
                          "social": "@Lexidriver"})

db.child(trialName).child(timeName).child("gps").update(
                         {"lat": 12.1212,
                          "long": 10.1223})

db.child(trialName).child(timeName).child("joulemeter").update(
                         {"amp": 25,
                         "avg": 154,
                         "instant": 100,
                         "peak": 100,
                          "volt": 23})

db.child(trialName).child(timeName).child("lap").update(
                         {"current": "1:40:23",
                          "fastest": "1:35:23",
                          "number": 2,
                          "remaining": "6:56:23",
                          "slowest": "1:40:23",
                          "total": "2:56:23"})

db.child(trialName).child(timeName).child("motor").update(
                         {"bhp": 12,
                          "temp": 45,
                          "volt": 12})

db.child(trialName).child(timeName).child("speed").update(
                         {"acceleration": 1.6,
                          "avg": 13,
                          "brake": 3,
                          "speed": 100,
                          "throttle": 10})

db.child(trialName).child(timeName).child("track").update(
                         {"name": "Sonoma Raceway",
                          "trial": 1,})

db.child(trialName).child(timeName).child("weather").update(
                         {"humidity": "45",
                          "temp": 78,
                          "weather": "Partly Cloudy"})
