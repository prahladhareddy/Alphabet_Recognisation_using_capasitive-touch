import numpy as np
import sys

alpha = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]

data = []
path = "../data/"
for i in range(26):
    A = np.loadtxt(path+alpha[i]+'data.txt')
    A = A.reshape(A.size//36,6,6)
    data.append(A)

def legal(x,y):
    if(x>=0 and x<6 and y>=0 and y<6 ):
        return True
    return False

def dist1(a,b,p,q):
    d = 0;
    for i in range(6):
        for j in range(6):
            x = i + p
            y = j + q
            if legal(x,y):
                if(a[x][y] == 0 and b[i][j] !=0):
                    d+=1
                if(a[x][y] != 0 and b[i][j] ==0):
                    d+=1
            else :
                if(b[i][j] != 1):
                    d+=1
    return d


def dist(a,b):
    dis = -1;
    for i in range(-3,4):
        for j in range(-3,4):
            x = dist1(a,b,i,j)
            if(dis == -1 or dis > x):
                dis = x
    return dis

def identify(a,k,use = 20):
    nei=[]
    ind = 0
    for i in range(26):
        ind = 0
        for mat in data[i]:
            if ind >= use:
                break
            d = dist(a,mat)
            if(len(nei) < k):
                nei.append([d,i,ind])
                nei.sort()
            elif nei[-1][0] > d:
                nei[-1] = [d,i,ind]
                nei.sort()
            ind+=1

    arr = [0]*26
    _max = 0
    _max_ind = 0
    for ar in nei:
        if ar[0] == 0:
            arr[ar[1]]+=10
        else :
            arr[ar[1]]+=1/ar[0]

    
    for i in range(26):
        if _max < arr[i]:
            _max = arr[i]
            _max_ind = i

    return alpha[_max_ind]
     

            
