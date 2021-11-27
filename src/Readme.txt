driver.py:  
    communicates with audrino 
    just module

    2 methods:

    connect() :
        starts listining to serial port /dev/ttyACM0 , returns true if successfull else false

    get_matri():
        looks for input from audruno and returns a (matrix , truth) if nothing exceptional then truth will be true else false

KNN.py:
    reads data from data folder
    just module

    identify(a,k,use = 20): 
        takes a 6x6 matrix and k and applies KNN algorithm using data from data folder 

    dist(a,b): 
        computes distance bw 2 6x6 matrices
        shifting origin distance (more details in ppt)

    dist1(a,b,p,q):
        finds distance by shifting a by (p,q)

alpha_rec.py:
    combiles driver and KNN
    Module

    init():
        starts the connection to audriuno

    getChar():
        takes matrix from audruino and applies KNN and returns the alphabet if recognised

identificationtest.py:
    uses alpha_rec.py to interactively show what is recognised when we scribble on grid

accuracytest.py:
    goes to data folder and reads the test files and applies KNN on that data
    5 test cases for each alphabet 
    it prints what alphabet is recognised as what and gives the accuracy

dataCollection.py:
    used in ndata collection phase 
    alphasbet and path are variables in this algorithm
    takes 5 input from grid and stores it in data files


