import time
import serial
import sys,tty,termios
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600, timeout=3)

s.write("/reverse/run 15 15 west\n".encode())
        
s = serial.Serial(sys.argv[1])
s.close()