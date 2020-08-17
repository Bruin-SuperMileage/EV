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
        my_dict[key] = my_dict[key] + 1
    my_list.append(str(my_dict))

    rpm_var.set("RPM: " + str(my_dict["Rpm"]) + " rpm")
    vlt_var.set("Voltage: " + str(my_dict["Vlt"]) + " V")
    cur_var.set("Current: " + str(my_dict["Cur"]) + " A")
    tmp_var.set("Temperature: " + str(my_dict["Tmp"]) + " F")
    pin_var.set("Power In: " + str(my_dict["Pin"]) + " W")
    pout_var.set("Power Out: " + str(my_dict["Pout"]) + " W")
    eff_var.set("Efficiency: " + str(my_dict["Eff"]) + " %")
    time_var.set("Time Duration: " + str(my_dict["Time"]))
    window.update()
#---------------------

#Define on_click function for button
def handle_click(event):
    if button["text"] == "Pause":
        button["text"] = "Run"
        #ser.write('P;')
        print("Flag was set to 'P;'")
        writeFile()
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
    'Cur' : -1,'Vlt' : -1,'Rpm' : -1,'Tmp' : -1,
    'Pin' : -1,'Pout' : -1,'Eff' : -1,'Time' : -1
    }
rpm_var = tk.StringVar()
vlt_var = tk.StringVar()
cur_var = tk.StringVar()
tmp_var = tk.StringVar()
pin_var = tk.StringVar()
pout_var = tk.StringVar()
eff_var = tk.StringVar()
time_var = tk.StringVar()
#---------------------

#Create the image of the dino
dino_img = ImageTk.PhotoImage(Image.open(dino_path).resize([150, 150]))
panel = tk.Label(window, image = dino_img, borderwidth=0)
panel.place(relx = 0.75, rely = 0.15, anchor='center')
#---------------------

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
label1 = tk.Label(window, textvariable=rpm_var, bg=color_bg, fg=color_label, font=font_text)
label1.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely'], anchor='w')

label2 = tk.Label(window, textvariable=vlt_var, bg=color_bg, fg=color_label, font=font_text)
label2.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely']+1*LABEL_SPACE, anchor='w')

label3 = tk.Label(window, textvariable=cur_var, bg=color_bg, fg=color_label, font=font_text)
label3.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely']+2*LABEL_SPACE, anchor='w')

label4 = tk.Label(window, textvariable=tmp_var, bg=color_bg, fg=color_label, font=font_text)
label4.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely']+3*LABEL_SPACE, anchor='w')
 
#Second column of labels
label5 = tk.Label(window, textvariable=pin_var, bg=color_bg, fg=color_label, font=font_text)
label5.place(relx = LABEL_COL2_PLACE['relx'], rely = LABEL_COL2_PLACE['rely'], anchor='w')

label6 = tk.Label(window, textvariable=pout_var, bg=color_bg, fg=color_label, font=font_text)
label6.place(relx = LABEL_COL2_PLACE['relx'], rely = LABEL_COL2_PLACE['rely']+1*LABEL_SPACE, anchor='w')

label7 = tk.Label(window, textvariable=eff_var, bg=color_bg, fg=color_label, font=font_text)
label7.place(relx = LABEL_COL2_PLACE['relx'], rely = LABEL_COL2_PLACE['rely']+2*LABEL_SPACE, anchor='w')

label8 = tk.Label(window, textvariable=time_var, bg=color_bg, fg=color_label, font=font_text)
label8.place(relx = LABEL_COL2_PLACE['relx'], rely = LABEL_COL2_PLACE['rely']+3*LABEL_SPACE, anchor='w')


window.mainloop()
#---------------------
