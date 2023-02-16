from tkinter import * #Tk, Label, Button, Entry, IntVar, END, W, E
from PIL import ImageTk, Image
from tkinter import ttk
import tkinter as tk
import _thread
import serial
import time
import os

#Assign serial port variables
port = 'COM4'
ard = serial.Serial(port,19200,timeout=5)

#bool for beaker selection
arduinoDisplay = " "
identifier = " "
msg = "Arduino: "
msg2 = "Status: "

s1 = " "
s2 = " "
s3 = " "
s4 = " "
s5 = " "
s6 = " "
s7 = " "

#Function to send string to Arduino

class AutoDriver:

    def __init__(self, master):
        self.master = master
        master.title("Auto Driver GUI")

        self.sixChosen = 7
        
        # feet = StringVar()
        self.CP = StringVar()
        self.SB = StringVar()
        self.beakers = StringVar()
        self.val = StringVar()
        self.t1 = StringVar()
        self.t2 = StringVar()
        self.t3 = StringVar()
        self.t4 = StringVar()
        self.t5 = StringVar()
        self.t6 = StringVar()
        self.t7 = StringVar()

        self.h1 = StringVar()
        self.h2 = StringVar()
        self.h3 = StringVar()
        self.h4 = StringVar()
        self.h5 = StringVar()
        self.h6 = StringVar()
        self.h7 = StringVar()

        #List for Time with numerical options
        self.timeopt = [1, 2, 3, 5, 10, 15]
        # self.timeopt = sorted(self.timeopt)
        self.t1.set(1) # set the default option
        self.t2.set(1) # set the default option
        self.t3.set(1) # set the default option
        self.t4.set(1) # set the default option
        self.t5.set(1) # set the default option
        self.t6.set(1) # set the default option
        self.t7.set(1) # set the default option      

        #List with Height options
        self.heightopt = [75 , 125, 150, 175, 200]
        # self.timeopt = sorted(self.timeopt)
        self.h1.set(75) # set the default option
        self.h2.set(75) # set the default option
        self.h3.set(75) # set the default option
        self.h4.set(75) # set the default option
        self.h5.set(75) # set the default option
        self.h6.set(75) # set the default option
        self.h7.set(75) # set the default option     

        #DECLARING THE BODY WIDGETS  
        
        self.label = Label(master, text="Logo")
        
        dirname = os.path.dirname(__file__) #finds local path
        filename = os.path.join(dirname, 'images/dipCoderGUILogo.gif') #attaches path to relative path
        self.img = ImageTk.PhotoImage(Image.open(filename))

        self.logoButton = Button(master, text="About", image = self.img, command=lambda: self.infoPopup())

        self.six_beakerButton = Button(master, text="6 Beakers", command=lambda: self.sixb(),height = 2)
        self.seven_beakerButton = Button(master, text="7 Beakers", relief=SUNKEN, command=lambda: self.sevenb(),height = 2)

        self.timeLabel = Label(master,background='#ABABAB', text="Submersion Time:", height="2", anchor="w" )
        self.heightLabel = Label(master,background='#ABABAB', text="Beaker Height:", height="2", anchor="w" )

        self.minuteLabel = Label(master,background='#CCCCCC', text="In\nMinutes", height="2", anchor="w" )
        self.mmLabel = Label(master,background='#CCCCCC', text="In\nMillimeters", height="2", anchor="w" )

        self.t1menu = OptionMenu(master, self.t1, *self.timeopt)
        self.t2menu = OptionMenu(master, self.t2, *self.timeopt)
        self.t3menu = OptionMenu(master, self.t3, *self.timeopt)
        self.t4menu = OptionMenu(master, self.t4, *self.timeopt)
        self.t5menu = OptionMenu(master, self.t5, *self.timeopt)
        self.t6menu = OptionMenu(master, self.t6, *self.timeopt)
        self.t7menu = OptionMenu(master, self.t7, *self.timeopt)

        self.t1menuLabel = Label(master, width="14", text="Beaker 1----->")
        self.t2menuLabel = Label(master, width="14", bg="#CCCCCC", text="Beaker 2----->")
        self.t3menuLabel = Label(master, width="14", text="Beaker 3----->")
        self.t4menuLabel = Label(master, width="14", bg="#CCCCCC", text="Beaker 4----->")
        self.t5menuLabel = Label(master, width="14", text="Beaker 5----->")
        self.t6menuLabel = Label(master, width="14", bg="#CCCCCC", text="Beaker 6----->")
        self.t7menuLabel = Label(master, width="14", text="Beaker 7----->")

        self.h1menu = OptionMenu(master, self.h1, *self.heightopt)
        self.h2menu = OptionMenu(master, self.h2, *self.heightopt)
        self.h3menu = OptionMenu(master, self.h3, *self.heightopt)
        self.h4menu = OptionMenu(master, self.h4, *self.heightopt)
        self.h5menu = OptionMenu(master, self.h5, *self.heightopt)
        self.h6menu = OptionMenu(master, self.h6, *self.heightopt)
        self.h7menu = OptionMenu(master, self.h7, *self.heightopt)

        self.h1menuLabel = Label(master, width="14", text="Beaker 1----->")
        self.h2menuLabel = Label(master, width="14", bg="#DDDDDD", text="Beaker 2----->")
        self.h3menuLabel = Label(master, width="14", text="Beaker 3----->")
        self.h4menuLabel = Label(master, width="14", bg="#DDDDDD", text="Beaker 4----->")
        self.h5menuLabel = Label(master, width="14", text="Beaker 5----->")
        self.h6menuLabel = Label(master, width="14", bg="#DDDDDD", text="Beaker 6----->")
        self.h7menuLabel = Label(master, width="14", text="Beaker 7----->")

        self.posTest_Button = Button(master, text="Position Test", command=lambda: self.PositionTest(), height=1, width=1)
        self.heightTest_Button = Button(master, text="Height Test", command=lambda: self.HeightTest(), height=1, width=1)

        self.send_button = Button(master, text="Send Values", command=lambda: self.SendData(),height=2,width=1, bg="yellow")
        self.stop_button = Button(master, text="STOP", command=lambda: self.StopDip(), height=2, width=1, bg="red")
        self.reset_button = Button(master, text="Reset", command =lambda: self.ResetDip(), height=2, width=1)
        self.quit_button = Button(master, text="Quit", command=self.master.destroy, height=2, width=1)

        self.start_button = Button(master, text="Start Program!", command=lambda: self.StartProgram(), height=1, width=1, bg="lightgreen")

        self.StatusBar = Label(master,background='White', text="Python GUI: 7 Beakers Selected", height="2", anchor="nw")
        self.ArduinoBar = Label(master,background='White', textvariable=self.CP, height="2", anchor="nw")

        # LAYOUT

        self.logoButton.grid(row=0, column=0, columnspan=4, sticky=W+E)

        self.six_beakerButton.grid(row=1, column=0, columnspan=2, sticky=W+E)
        self.seven_beakerButton.grid(row=1, column=2, columnspan=2, sticky=W+E)

        self.timeLabel.grid(row=2, column=0, columnspan=1, sticky=W+E)
        self.minuteLabel.grid(row=2, column=1, columnspan=1, sticky=W+E)

        self.heightLabel.grid(row=2, column=2, columnspan=1, sticky=W+E)
        self.mmLabel.grid(row=2, column=3, columnspan=1, sticky=W+E)

        # BEAKER TIMING MENU DROPDOWN      

        self.t1menu.grid(column=1, sticky=W+E, row=4)
        self.t2menu.grid(column=1, sticky=W+E, row=5)
        self.t3menu.grid(column=1, sticky=W+E, row=6)
        self.t4menu.grid(column=1, sticky=W+E, row=7)
        self.t5menu.grid(column=1, sticky=W+E, row=8)
        self.t6menu.grid(column=1, sticky=W+E, row=9)
        self.t7menu.grid(column=1, sticky=W+E, row=10)

        self.t1menuLabel.grid(column=0, sticky=W+E, row=4)
        self.t2menuLabel.grid(column=0, sticky=W+E, row=5)
        self.t3menuLabel.grid(column=0, sticky=W+E, row=6)
        self.t4menuLabel.grid(column=0, sticky=W+E, row=7)
        self.t5menuLabel.grid(column=0, sticky=W+E, row=8)
        self.t6menuLabel.grid(column=0, sticky=W+E, row=9)
        self.t7menuLabel.grid(column=0, sticky=W+E, row=10)

        self.h1menu.grid(column=3, sticky=W+E, row=4)
        self.h2menu.grid(column=3, sticky=W+E, row=5)
        self.h3menu.grid(column=3, sticky=W+E, row=6)
        self.h4menu.grid(column=3, sticky=W+E, row=7)
        self.h5menu.grid(column=3, sticky=W+E, row=8)
        self.h6menu.grid(column=3, sticky=W+E, row=9)
        self.h7menu.grid(column=3, sticky=W+E, row=10)

        self.h1menuLabel.grid(column=2, sticky=W+E, row=4)
        self.h2menuLabel.grid(column=2, sticky=W+E, row=5)
        self.h3menuLabel.grid(column=2, sticky=W+E, row=6)
        self.h4menuLabel.grid(column=2, sticky=W+E, row=7)
        self.h5menuLabel.grid(column=2, sticky=W+E, row=8)
        self.h6menuLabel.grid(column=2, sticky=W+E, row=9)
        self.h7menuLabel.grid(column=2, sticky=W+E, row=10)

        # BUTTONS AND STATUS BAR
                     
        self.posTest_Button.grid(row=11, column=0, columnspan=2, sticky=W+E)
        self.heightTest_Button.grid(row=11, column=2, columnspan=2, sticky=W+E)      

        self.send_button.grid(row=12, column=0, sticky=W+E)
        self.stop_button.grid(row=12, column=1, sticky=W+E)
        self.reset_button.grid(row=12, column=2, sticky=W+E)
        self.quit_button.grid(row=12, column=3, sticky=W+E)

        self.start_button.grid(column=0, columnspan=4, row=13, sticky=W+E)

        # STATUS BAR

        self.StatusBar.grid(column=0, columnspan=4, row=14, sticky=W+E)

        # ARDUINO STATUS BAR

        self.ArduinoBar.grid(column=0, columnspan=4, row=15, sticky=W+E)

        self.master.after(2500, _thread.start_new_thread, self.updateStatus,())

    def sixb(self):
        self.six_beakerButton.config(relief=SUNKEN)
        self.seven_beakerButton.config(relief=RAISED)
        self.StatusBar.configure(text = "Python GUI: 6 Beakers Selected")
        self.sixChosen = 6
        print(self.sixChosen)
        self.t7menu.grid_remove()
        self.t7menuLabel.grid_remove()
        self.h7menu.grid_remove()
        self.h7menuLabel.grid_remove()

    def sevenb(self):
        self.seven_beakerButton.config(relief=SUNKEN)
        self.six_beakerButton.config(relief=RAISED)
        self.StatusBar.configure(text = "Python GUI: 7 Beakers Selected")
        self.sixChosen = 7
        print(self.sixChosen)
        self.t7menu.grid()
        self.t7menuLabel.grid()
        self.h7menu.grid()
        self.h7menuLabel.grid()

    def infoPopup(self):
        newWindow = Toplevel(root) 
        newWindow.title("About") 
        newWindow.geometry("300x100") 
        Label(newWindow,  
        text ="Developed By Michael Hnatiuk & David Kimball\nCopyright 2020\nContact: davidkkimball@gmail.com\nmikehnatiuk@gmail.com\nv0.1alpha").pack() 

    def PositionTest (self):
        #Send position values to Arduino
        identifier = "runPos"
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        self.StatusBar.configure(text = "Python GUI: Preforming Position Test, Please Wait...")
        time.sleep(1)
        print (self.sendMe)

    def HeightTest (self):
        #Send height values to Arduino
        identifier = "runH"
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        self.StatusBar.configure(text = "Python GUI: Preforming Height Test, Please Wait...")
        time.sleep(2)
        print (self.sendMe)

    def SendData(self):
        #Write values to variables, height first
        s1 = self.h1.get()
        s2 = self.h2.get()
        s3 = self.h3.get()
        s4 = self.h4.get()
        s5 = self.h5.get()
        s6 = self.h6.get()
        s7 = self.h7.get()
        #Send Height values to Arduino and wait for buffer
        self.StatusBar.configure(text = "Python GUI: Sending Height data to Arduino, Please Wait...")
        identifier = "sendD"
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        print (self.sendMe) 
        time.sleep(5)       
        #Write values to variables, time second
        s1 = self.t1.get()
        s2 = self.t2.get()
        s3 = self.t3.get()
        s4 = self.t4.get()
        s5 = self.t5.get()
        s6 = self.t6.get()
        s7 = self.t7.get()
        #Send Height values to Arduino and wait for buffer
        self.StatusBar.configure(text = "Python GUI: Sending Time data to Arduino, Please Wait...")
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        time.sleep(1)
        #Get response from Arduino to confirm data transfer successfully
        print (self.sendMe)

    def StartProgram(self):
        #Send to Arduino
        identifier = "startP"
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        self.StatusBar.configure(text = "Python GUI: Arduino Program Starting, Please Wait...")
        time.sleep(1)
        print (self.sendMe)

    def ResetDip (self):
        #Reset
        identifier = "reset"
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        self.StatusBar.configure(text = "Python GUI: Resetting Dipcoder Values, Please Wait...")
        time.sleep(1)
        print (self.sendMe)

    def StopDip (self):
        #E-Stop
        identifier = "quit"
        self.sendMe = str(identifier + ',' + s1 + ',' + s2 + ',' + s3 + ',' + s4 + ',' + s5 + ',' + s6 + ',' + s7 + "*")
        ard.write(self.sendMe.encode())
        self.StatusBar.configure(text = "Python GUI: Stopping Dipcoder, Please Wait...")
        time.sleep(1)
        print (self.sendMe)

    def ResetStatusBar (self):
        #Re-check Beaker and display
        #time.sleep(2) //Adjust the timing 
        if self.sixChosen == 6 :
            self.StatusBar.configure(text = "Python GUI: 6 Beakers Selected")
        if self.sixChosen == 7 :
            self.StatusBar.configure(text = "Python GUI: 7 Beakers Selected")          

    def updateStatus (self):
        while(1):
            v = ard.read(ard.inWaiting())
            self.val = v.decode('utf-8')
            if self.val != " ":
                self.CP.set(str(self.val))
                self.CP.set(msg + self.val)
                time.sleep(2)
                # self.ResetStatusBar()
                self.master.after(5, self.ResetStatusBar())
            else :
                time.sleep(1)


root = Tk()
my_gui = AutoDriver(root)
root.mainloop()