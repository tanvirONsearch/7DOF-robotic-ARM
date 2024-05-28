import serial
import time
arduino=serial.Serial('com3',115200)
mssg="box"
while True:
    mssg="ab"
    mssg=mssg+'\r'
    arduino.write(mssg.encode())
    time.sleep(1)
    