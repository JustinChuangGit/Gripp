import serial
import time

arduino = serial.Serial(port='/dev/tty.usbserial-0001', baudrate=115200, timeout=5)
#Check com port in terminal(ls /dev/tty.*)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(5)
    data = str(arduino.readline())
    data = data.split('\\',1)[0]
    data = data.strip("b'-")
    return data

while True:
    num = input("Enter a number: ") # Taking input from user
    value = write_read(num)
    print(value)
    

