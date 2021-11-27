import KNN
import driver

def init():
    return driver.connect()

def getChar() :
    (A,e) = driver.get_matrix()
    print(A)
    if e == False :
        return None
    return KNN.identify(A,3)


