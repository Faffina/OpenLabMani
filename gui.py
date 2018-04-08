#!/usr/bin/env python3
import time
from tkinter import *
import serial

ser = serial.Serial('/dev/ttyACM0', 9600) 
data = {"a":[], "b":[],"c":[],"d":[]}

def serDectpit():
    mess = ser.readline().decode("utf-8")
    mylist.insert(END,mess)

root = Tk()
scrollbar = Scrollbar(root)
scrollbar.pack( side = RIGHT, fill = Y )

mylist = Listbox(root, yscrollcommand = scrollbar.set )

mylist.pack( side = LEFT, fill = BOTH )
scrollbar.config( command = mylist.yview )

while True:
    serDectpit()
    root.update_idletasks()
    root.update()
