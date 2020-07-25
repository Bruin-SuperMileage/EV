import tkinter as tk
import serial

#Create the viewable window
window = tk.Tk()
#---------------------
#Define constants
NUMSENSORS1 = 2 #RPM AND TEMPERATURE
NUMSENSORS2 = 2 #JOULEMETER
#---------------------

#Initialize variables
my_list = []
#declare the dictionary to store all input data
my_dict={
    'Cur' : -1,'Vlt' : -1,'Rpm' : -1,'Tmp' : -1
    }
#---------------------

#Define on_click function for button
def handle_click(event):
    if button["text"] == "Pause":
        button["text"] = "Run"
#        ser.write('P;')
        print("Flag was set to 'P;'")
        f = open("demofile2.txt", "a")
        f.write(my_list)
        f.close()
    else:
        button["text"] = "Pause"
#        ser.write('R;')
        print("Flag was set to 'R;'")
        update_label()
#---------------------

#Update the variables for the labels
def update_label():
    while 1:
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
        my_list.append(my_dict)
        window.update()
#---------------------

#Open the serial port that the MCU is connected to
#ser1 = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.01)
#ser2 = serial.Serial('/dev/ttyUSB1', 9600, timeout=0.01)
#---------------------

#Create the title of the window
label = tk.Label(text="Dynomometer Control Panel", padx=5, pady=5)
label.pack()
#---------------------

#Create the interactive button
button = tk.Button(text = "Pause")
button.pack()
button.bind("<Button-1>", handle_click)
#---------------------

#Create labels to display sensor readings
label = tk.Label(text="RPM: " + str(my_dict["Rpm"]))
label.pack()

label = tk.Label(text="Voltage: " + str(my_dict["Vlt"]))
label.pack()

label = tk.Label(text="Current: " + str(my_dict["Cur"]))
label.pack()

label = tk.Label(text="Temperature: " + str(my_dict["Tmp"]))
label.pack()

window.mainloop()
#---------------------
