"""Dyno Dashboard

Usage:
  dyno_panel.py
  dyno_panel.py (-n | --no_serial) 
  dyno_panel.py (-h | --help)

Options:
  -h --help     Show this screen.
  --no_serial   Run in debug mode without reading MCU data

"""

from docopt import docopt
arguments = docopt(__doc__)

import tkinter as tk
from tkinter import font
from PIL import Image, ImageTk
import serial
import datetime
import math

#Define constants
LEXI_NUMSENSORS = 2 #RPM AND TEMPERATURE
OLIVER_NUMSENSORS = 2 #JOULEMETER
READ_SERIAL_ON = False if arguments.get("--no_serial") else True
loop_speed = 100 #ms
window_width = 800
window_height = 600
FLAG_RUN = False

num_magnets = 8
magnet_radius = 50
default_magnet = [0,8,0,8,0,8,0,8]
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
    if FLAG_RUN:
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
                check_acknowledge();
        else:
            for key in data_output_dict.keys():
                data_output_dict[key][1] = data_output_dict[key][1] + 1
        
        text_file_data.append({str(datetime.datetime.now()):str(data_output_dict.values())})

    temp = list(data_output_dict.values())
    for i in range(num_vars):
        tk_stringvars[i].set(temp[i][0] + str(temp[i][1]) + temp[i][2])
    window.after(loop_speed, update_labels)
#---------------------

#Define on_click function for button
def handle_click(event):
    global FLAG_RUN, text_file_data

    if start_button["text"] == "Pause":
        start_button["text"] = "Run"
        if READ_SERIAL_ON:
            driver.write('P;')
        print("Flag was set to 'P;'")
        FLAG_RUN = False
        writeFile()
        update_labels()
    elif start_button["text"] == "Run":
        start_button["text"] = "Pause"
        text_file_data = []
        if READ_SERIAL_ON:
            driver.write('R;')
        FLAG_RUN = True
        print("Flag was set to 'R;'")
#---------------------

def map(x, in_min, in_max, out_min, out_max):
    return int((x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min)
#---------------------

def push_config(event):
    magnet_config = "magnets="
    for i in range(num_magnets):
        pwm = int(magnet_tkvars[i].get())
        if pwm < 0:
            pwm = 0
        elif pwm > 9:
            pwm = 9
        pwm = str(map(pwm, 0, 9, 0, 255)).zfill(3)
        magnet_config = magnet_config + str(i) + ":" + pwm + ","
    magnet_config = magnet_config[:-1] + ";"
    if READ_SERIAL_ON:
        driver.write(magnet_config)
    print(magnet_config)

    throttle = int(throttle_slider.get())
    if throttle < 0:
        throttle = 0
    elif throttle > 100:
        throttle = 100
    throttle = str(map(throttle, 0, 100, 0, 255)).zfill(3)
    throttle_config = "motor=" + throttle + ";"
    if READ_SERIAL_ON:
        driver.write(throttle_config)
    print(throttle_config)
    mcu_acknowledged=False
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
window.configure(bg=color_bg)
window.geometry(str(window_width)+"x"+str(window_height))
font_title = font.Font(family="Helvetica", size=36, weight="bold")
font_text = font.Font(family="Helvetica", size=24)
font_magnet = font.Font(family="Helvetica", size=16, weight="bold")
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

magnet_tkvars = []
for i in range(num_magnets):
    magnet_tkvars.append(tk.StringVar())
    magnet_tkvars[i].set(str(default_magnet[i]))
#---------------------

#Create the image of the dino
dino_img = ImageTk.PhotoImage(Image.open(dino_path).resize([150, 150]))
panel = tk.Label(window, image = dino_img, borderwidth=0)
panel.place(relx = 0.73, rely = 0.15, anchor='center')

#Create the title of the window
dyno_title = tk.Label(text="Project Dyno", bg=color_bg, fg=color_fg, font=font_title)
dyno_title.place(relx = 0.5, rely = 0.18, anchor='center')
#---------------------

#Create the start/stop button
start_img = ImageTk.PhotoImage(Image.open(start_path).resize([70, 70]))
start_button = tk.Button(bg = color_bg, activebackground = color_bg, text = "Run", image = start_img, borderwidth = 0)
start_button.place(relx = 0.5, rely = 0.35, anchor='center')
start_button.bind("<Button-1>", handle_click)
#---------------------

#Create labels to display sensor readings
for i in range(int(num_vars)): #First Column
    data_label = tk.Label(window, textvariable=tk_stringvars[i], bg=color_bg, fg=color_label, font=font_text)
    data_label.place(relx = LABEL_COL1_PLACE['relx'], rely = LABEL_COL1_PLACE['rely']+i*LABEL_SPACE, anchor='w')
#---------------------

#Create entry fields to get magnet values
magnet_canvas = tk.Canvas(window, width=150, height=150, bg=color_bg)
magnet_canvas.place(relx=0.75, rely=0.55, anchor="center")
magnet_title = tk.Label(window, text="Magnets", bg=color_bg, fg=color_fg, font=font_magnet)
magnet_canvas.create_window(75, 0, window=magnet_title)
for i in range(num_magnets):
    magnet_entry = tk.Entry(window, width=2, font=font_magnet, text=magnet_tkvars[i], bg=color_label)
    x = math.cos(2*math.pi/num_magnets*i)*magnet_radius
    y = math.sin(2*math.pi/num_magnets*i)*magnet_radius
    magnet_canvas.create_window(x+75, y+80, window=magnet_entry)
#---------------------

#Create slider to get throttle position
throttle_canvas = tk.Canvas(window, width=150, height=70, bg=color_bg)
throttle_canvas.place(relx=0.75, rely=0.77, anchor="center")
throttle_title = tk.Label(window, text="Throttle", bg=color_bg, fg=color_fg, font=font_magnet)
throttle_canvas.create_window(75, 0, window=throttle_title)
throttle_slider = tk.Scale(window, from_=0, to=100, orient=tk.HORIZONTAL, bg=color_label)
throttle_canvas.create_window(75, 45, window=throttle_slider)
#---------------------
def check_acknowledge():
    if not mcu_acknowledged:
        data = driver.read()
        if ack = "200;":
            mcu_acknowledged = True
       
#---------------------
#Create the push button
push_button = tk.Button(bg = color_bg, activebackground = color_bg, fg=color_fg, text = "Push", font=font_magnet)
push_button.place(relx = 0.75, rely = 0.89, anchor='center')
push_button.bind("<Button-1>", push_config)
#---------------------

#Create smv label
smv_label = tk.Label(window, text="made by Bruin SuperMileage", bg=color_bg, fg=color_fg, font=font_magnet)
smv_label.place(relx = 0.99, rely = 0.97, anchor='e')

window.after(loop_speed, update_labels)
window.mainloop()
#---------------------
