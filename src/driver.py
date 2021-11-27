from serial import Serial
import sys


def connect():
    print(True)
    serialPort = "/dev/ttyACM0"
    try :
        global ser 
        ser = Serial(serialPort, baudrate=9600)
    except :
        return False
    return True

def get_matrix():
    flag = 0
    A = []
    ser.flush()
    for i in range(200):
        while ser.in_waiting <= 0:
            pass
        byte_str = ser.read_until()
        read_str = byte_str.decode("utf-8")
        if "MATRIX" in read_str:
            flag = 1;
        elif flag > 0:
            A.append(list(map(int,read_str.split())))
            if flag == 6:
                flag = -1
                return (A,True)
            flag+=1
    
    return (A,False)
