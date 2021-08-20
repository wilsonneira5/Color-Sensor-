import serial
import tkinter as tk
import os
from threading import Thread
from serial import *
  

last_received = ''

def receiving(ser):

    global last_received

    buffer = ''

    while True:

        last_received = ser.readline()

        buffer += ser.read(ser.inWaiting())

        if '\n' in buffer:

            last_received, buffer = buffer.split('\n')[-2:]


    #Create Thread
    Thread(target=receiving, args=(ser,)).start()
def readColor():
      #Initial Box Color
      c="black"
      #Initial Text Color
      t="Black"
      ser.flushInput()
      ser.write(bytes("l","ASCII"))
     
      
      x = 0
      while x<1:
          
          
          arduino  = ser.readline().decode('ASCII')
         
          arduino2 = ser.readline().decode('ASCII')

          arduinoList = list(arduino)
          arduinoList2 = list(arduino2)

          arduinoData = "1"
          arduinoData2 = "1"
          
          z=0
          for s in arduinoList:
                if s == 'D':
                     z=1 
          if z == 1:
                      arduinoData2 = arduino
          else:
                      arduinoData = arduino

          q=0
          for t in arduinoList2:
                if t == 'D':
                     q=1 
          if q == 1:
                      arduinoData2 = arduino2
          else:
                      arduinoData = arduino2
      
          
          x=x+1
      
      print(arduinoData)
      rgbList = arduinoData2.split(',')

      print(rgbList)

      brown = "#993300"
      purple = "#6a0dad"
      gray = "#bebebe"
      orange = "#ff6600"
      pink = "#ffc0cb"

      for n in rgbList:
            if n=='Black Color Detected\r\n':
             c="black"
             t="Black"
            elif n=='Blue Color Detected\r\n':
             c="blue"
             t="Blue"
            elif n=='Red Color Detected\r\n':
             c="red"
             t="Red"
            elif n=='Brown Color Detected\r\n':
             c=brown
             t="Brown"
            elif n=='Purple Color Detected\r\n':
             c=purple
             t="Purple"
            elif n=='Green Color Detected\r\n':
             c="green"
             t="Green"
            elif n=='Gray Color Detected\r\n':
             c=gray
             t="Gray"
            elif n=='Orange Color Detected\r\n':
             c=orange
             t="Orange"
            elif n=='Yellow Color Detected\r\n':
             c="yellow"
             t="Yellow"
            elif n=='Pink Color Detected\r\n':
             c=pink
             t="Pink"
            elif n=='White Color Detected\r\n':
             c="white"
             t="White"
      
      
      canvas.itemconfig(rec, fill= c)
      canvas.itemconfig(CText, fill = c, text = t)
      canvas.update
      
   
ser=serial.Serial('com9',baudrate = 9600)

win = tk.Tk()
win.title("Computer Organization and Arquitecture Honors: Color Sensor")
win.geometry("800x800+500+100")
#Set window resizable to false.
win.resizable(width=False,height=False)
#win.iconbitmap("11-Colors.ico")
win.iconphoto(False, tk.PhotoImage(file="11-Colors.png"))
canvas=tk.Canvas(win,width=1940, height=1220, bg = "blanchedalmond")

TText=canvas.create_text(400,50,fill="coral",font="helvetica 42 bold",text="Adafruit Color Sensor")
rec=canvas.create_rectangle(250, 150, 550, 450, fill="black")
CText=canvas.create_text(400,500,fill="black",font="helvetica 35 bold",text="No Color Detected")
 
canvas.pack(fill = tk.BOTH, expand = tk.YES)

bt1 = tk.Button(text="Detect Color",command=readColor, bg="brown", fg="white", font=("helvetica", 22, "bold"))
canvas.create_window(400, 600, window=bt1)

 
win.mainloop()
 
 
 
 



