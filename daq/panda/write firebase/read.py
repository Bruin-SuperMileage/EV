#this file works completely perfectly
#do not mess up this file


#THIS FILE READS DATA FROM FIREBASE's SPEED DATA POINT AND PRINTS THE VALUE

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

users = db.child("speed").get()

print(users.val()) 
