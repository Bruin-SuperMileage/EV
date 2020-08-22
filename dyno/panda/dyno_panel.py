import tkinter as tk
from tkinter import font
from PIL import Image, ImageTk
import serial
import time

#Define constants
LEXI_NUMSENSORS = 2 #RPM AND TEMPERATURE
OLIVER_NUMSENSORS = 2 #JOULEMETER
READ_SERIAL_ON = False
loop_speed = 100 #ms
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
LABEL_COL1_PLACE = {'relx':0.15, 'rely':0.45}
LABEL_COL2_PLACE = {'relx':0.55, 'rely':0.4}
LABEL_SPACE = 0.07
#---------------------

#Open the serial port that the MCU is connected to
if READ_SERIAL_ON:
    t_out = 0.5
    lexi = serial.Serial('/dev/ttyUSB0', 9600, timeout=t_out)
    oliver = serial.Serial('/dev/ttyUSB1', 9600, timeout=t_out)
    driver = serial.Serial('/dev/ttyUSB2', 9600, timeout=t_out)
#---------------------

#Update the variables for the labels
def update_labels():
    #Read in input from MCU sensors
    if READ_SERIAL_ON:
        for x in range (0, LEXI_NUMSENSORS): #read Lexi sensor data
            val = lexi.readline().decode('ascii')
            prefix = val[0:3]
            data_output_dict[prefix] = float(val[5:-2])
        for x in range (0, OLIVER_NUMSENSORS): #read Oliver sensor data
            val = oliver.readline().decode('ascii')
            prefix = val[0:3]
            data_output_dict[prefix] = float(val[5:-2])
    else:
        for key in data_output_dict.keys():
            data_output_dict[key][1] = data_output_dict[key][1] + 1
    
    text_file_data.append(str(data_output_dict))

    temp = list(data_output_dict.values())
    for i in range(num_vars):
        tk_stringvars[i].set(temp[i][0] + str(temp[i][1]) + temp[i][2])

    window.after(loop_speed, update_labels)
#---------------------

#Define on_click function for button
def handle_click(event):
    if button["text"] == "Pause":
        button["text"] = "Run"
        if READ_SERIAL_ON:
            driver.write('P;')
        print("Flag was set to 'P;'")
        writeFile()
        update_labels()
    elif button["text"] == "Run":
        button["text"] = "Pause"
        if READ_SERIAL_ON:
            driver.write('R;')
        print("Flag was set to 'R;'")
#---------------------

#Write to text file
def writeFile():
    f = open("demofile.txt", "a")
    f.write(str(text_file_data))
    f.write('\n')
    f.close()
#---------------------

#Create the viewable window
window = tk.Tk()
window.configure(bg= color_bg)
window.geometry("800x600")
font_title = font.Font(family="Helvetica", size=36, weight="bold")
font_text = font.Font(family="Helvetica", size=24)
#---------------------

#Initialize variables
text_file_data = []
data_output_dict = {
    'Cur' : ["Current: ", -1, " A"],
    'Vlt' : ["Voltage: ", -1, " V"],
    'Rpm' : ["RPM: ", -1, " rpm"],
    'Tmp' : ["Temperature: ", -1, " F"],
    'Pin' : ["Power In: ", -1, " W"],
    'Pout' : ["Power Out: ", -1, " W"],
    'Eff' : ["Efficiency: ", -1, " %"],
    'Time' : ["Time Duration: ", -1, " "]
    }
num_vars = len(data_output_dict)

tk_stringvars = []
for i in range(num_vars):
    tk_stringvars.append(tk.StringVar())
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
start_img = ImageTk.PhotoImage(Image.open(start_path).resize([70, 70]))
button = tk.Button(bg = color_bg, activebackground = color_bg, text = "Pause", image = start_img, borderwidth = 0)
button.place(relx = 0.5, rely = 0.35, anchor='center')
button.bind("<Button-1>", handle_click)
#---------------------

#Create labels to display sensor readings
for i in range(int(num_vars)): #First Column
    label1 = tk.Label(window, textvariable=tk_stringvars[i], bg=color_bg, fg=color_label, font=font_text)
    label1.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely']+i*LABEL_SPACE, anchor='w')

window.after(loop_speed, update_labels)
window.mainloop()
#---------------------
