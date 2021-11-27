import sys
import KNN
import numpy as np

alpha = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]

err = np.zeros( (26, 26) )
count = 0
data = []
path = "../data/"
for i in range(26):
    A = np.loadtxt(path+alpha[i]+'test.txt')
    A = A.reshape(A.size//36,6,6)
    data.append(A)

for i in range(26):
    for j in range(5):
        c = KNN.identify(data[i][j],7)
        err[i][ord(c)-ord('A')]+=1
        print(alpha[i], c)
        if(alpha[i]==c):
            count+=1;

print(err)
print(count)
print(count/(26*5))
