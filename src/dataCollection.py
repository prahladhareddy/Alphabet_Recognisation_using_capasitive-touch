# import pygame

from serial import Serial
import sys

serialPort = "/dev/ttyACM0"
ser = Serial(serialPort, baudrate=9600)

alp = "Z"  # modify here to change the alphabet 
flag = 0
count = 0

fname = "../data/"+alp+"test.txt" # modify here to change path and file name
file = open(fname,'a')

while(True):
    if count == 5:  # change count depending on number of data points you are taking as input
        break
    if ser.in_waiting > 0:
        byte_str = ser.read_until()
        read_str = byte_str.decode("utf-8")
        print(read_str)
        if "MATRIX" in read_str:
            flag = 1;
        elif flag > 0:
            file.write(read_str)
            if flag == 6:
                flag = -1
                count+=1
                file.write("\n")
            flag+=1