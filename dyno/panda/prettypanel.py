import tkinter as tk
from tkinter.ttk import *
from tkinter import font
import serial

#Define constants
NUMSENSORS = 4
path = "./dino.jpg"
#---------------------

#Initialize variables
rpm = "-1"
cur = "-1"
volt = "-1"
temp = "-1"
#---------------------

#Define on_click function for button
def handle_click(event):
    if button["text"] == "Pause":
        button["text"] = "Run"
#        ser.write('P')
        print("Flag was set to 'P'")
    else:
        button["text"] = "Pause"
#        ser.write('R')
        print("Flag was set to 'R'")
#---------------------

#Open the serial port that the MCU is connected to
#ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.5)
#---------------------

#Create the viewable window
window = tk.Tk()
window.configure(bg="#16495C")
myTitle = font.Font(family="Helvetia",size=36,weight="bold")
#---------------------

#Create the title of the window
label = tk.Label(text="Project Dyno", padx=15, pady=15, bg="#16495C", fg="#DA8669", font=myTitle)
label.pack(side="left")
#---------------------

#Create the image of the dino
img = PhotoImage(file = r"./dino.gif")
panel = tk.Label(window, image = img)
panel.pack(side = "left", fill = "none", expand = "no")
#---------------------

#Create the interactive button
button = tk.Button(text = "Pause")
button.pack(side="bottom")
button.bind("<Button-1>", handle_click)
#---------------------

#Read in input from MCU sensors
#for x in range (0, NUMSENSORS): #read sensor statements
#    val = ser.readline().decode('ascii')
#    prefix = val[0:3]
#    if (prefix == "Cur"):
#        cur = float(val[5:-2])
#    if (prefix == "Vlt"):
#        volt = float(val[5:-2])
#    if (prefix == "RPM"):
#        rpm = float(val[5:-2])
#    if (prefix == "Tmp"):
#        temp = float(val[5:-2])
#---------------------

#Create labels to display sensor readings
label = tk.Label(text="RPM: " + rpm)
label.pack(side="bottom")

label = tk.Label(text="Voltage: " + volt)
label.pack()

label = tk.Label(text="Current: " + cur)
label.pack()

label = tk.Label(text="Temperature: " + temp)
label.pack()
#---------------------

window.mainloop()

