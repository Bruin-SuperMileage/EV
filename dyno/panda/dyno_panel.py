import tkinter as tk
from tkinter import font
from PIL import Image, ImageTk
import serial
import time

#Define constants
NUMSENSORS1 = 2 #RPM AND TEMPERATURE
NUMSENSORS2 = 2 #JOULEMETER
#---------------------

#Images
dino_path = "./img/dino.gif"
start_path = "./img/start.png"
#---------------------

#Colors
color_bg = "#16495C"
color_fg = "#DA8669"
color_label = "#B1D9DB"
#---------------------

#Placement
LABEL_COL1_PLACE = {'relx':0.15, 'rely':0.6}
LABEL_COL2_PLACE = {'relx':0.55, 'rely':0.6}
LABEL_SPACE = 0.08
#---------------------

#Open the serial port that the MCU is connected to
'''ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.5)'''
#---------------------

#Update the variables for the labels
def update_labels():
    #Read in input from MCU sensors
    '''for x in range (0, NUMSENSORS1): #read sensor statements
        val = ser1.readline().decode('ascii')
        prefix = val[0:3]
        my_dict[prefix] = float(val[5:-2])
    for x in range (0, NUMSENSORS2): #read JOULEMETER statements
        val = ser2.readline().decode('ascii')
        prefix = val[0:3]
        my_dict[prefix] = float(val[5:-2])'''
    for key in my_dict.keys():
        my_dict[key][1] = my_dict[key][1] + 1
    my_list.append(str(my_dict))

    temp = list(my_dict.values())
    
    for i in range(num_vars):
        var_array[i].set(temp[i][0] + str(temp[i][1]) + temp[i][2])

    window.after(100, update_labels)
#---------------------

#Define on_click function for button
def handle_click(event):
    if button["text"] == "Pause":
        button["text"] = "Run"
        #ser.write('P;')
        print("Flag was set to 'P;'")
        writeFile()
        update_labels()
    elif button["text"] == "Run":
        button["text"] = "Pause"
        #ser.write('R;')
        print("Flag was set to 'R;'")
#---------------------

#Write to text file
def writeFile():
    f = open("demofile.txt", "a")
    f.write(str(my_list))
    f.write('\n')
    f.close()
#---------------------

#Create the viewable window
window = tk.Tk()
window.configure(bg= color_bg)
window.geometry("800x500")
font_title = font.Font(family="Helvetia", size=36, weight="bold")
font_text = font.Font(family="Helvetia", size=24)
#---------------------

#Initialize variables
my_list = []
my_dict={
    'Cur' : ["Current: ", -1, " A"],
    'Vlt' : ["Voltage: ", -1, " V"],
    'Rpm' : ["RPM: ", -1, " rpm"],
    'Tmp' : ["Temperature: ", -1, " F"],
    'Pin' : ["Power In: ", -1, " W"],
    'Pout' : ["Power Out: ", -1, " W"],
    'Eff' : ["Efficiency: ", -1, " %"],
    'Time' : ["Time Duration: ", -1, " "]
    }
num_vars = len(my_dict)

var_array = []
for i in range(num_vars):
    var_array.append(tk.StringVar())
#---------------------

#Create the image of the dino
dino_img = ImageTk.PhotoImage(Image.open(dino_path).resize([150, 150]))
panel = tk.Label(window, image = dino_img, borderwidth=0)
panel.place(relx = 0.75, rely = 0.15, anchor='center')

#Create the title of the window
label = tk.Label(text="Project Dyno", padx=15, pady=15, bg=color_bg, fg=color_fg, font=font_title)
label.place(relx = 0.5, rely = 0.21, anchor='center')
#---------------------

#Create the start/stop button
start_img = ImageTk.PhotoImage(Image.open(start_path).resize([100, 100]))
button = tk.Button(bg = color_bg, activebackground = color_bg, text = "Pause", image = start_img, borderwidth = 0)
button.place(relx = 0.5, rely = 0.4, anchor='center')
button.bind("<Button-1>", handle_click)
#---------------------

#Create labels to display sensor readings
for i in range(int(num_vars/2)): #First Column
    label1 = tk.Label(window, textvariable=var_array[i], bg=color_bg, fg=color_label, font=font_text)
    label1.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely']+i*LABEL_SPACE, anchor='w')

for i in range(int(num_vars/2), num_vars): #Second Column
    label2 = tk.Label(window, textvariable=var_array[i], bg=color_bg, fg=color_label, font=font_text)
    label2.place(relx = LABEL_COL2_PLACE['relx'], rely = LABEL_COL2_PLACE['rely']+(i-4)*LABEL_SPACE, anchor='w')

window.after(100, update_labels)
window.mainloop()
#---------------------
