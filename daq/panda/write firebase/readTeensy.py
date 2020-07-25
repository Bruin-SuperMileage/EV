#this file works completely perfectly
#do not mess up this file

#THIS FILE READS DATA FROM THE COM6 SERIAL MONITOR AND PRINTS THE VALUE

import serial

s = serial.Serial('COM6', baudrate = 9600, timeout = 1)

while (1):
    res = s.readline().decode('ascii')
    print(res)
