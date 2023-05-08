import numpy as np; import pandas as pd
import seaborn as sbn; import matplotlib.pyplot as plt
import time
import random 
from sympy import symbols, Eq
import math
from sklearn.model_selection import train_test_split
from sklearn import datasets;

def horner(A, x0):
    """ input: A = [a_n,...,a_1,a_0]
        output: p,d = P(x0),DP(x0) = horner(A,x0) """
    n = len(A)
    p = A[0]; d = 0

    for i in range(1,n):
        d = p + x0*d
        p = A[i] +x0*p
    return p,d

def newton_horner(A,x0,tol,itmax):
    """ input: A = [a_n,...,a_1,a_0]
    output: x: P(x)=0 """
    x=x0
    
    for it in range(1,itmax+1):
        p,d = horner(A,x)
        h = -p/d;
        x = x + h;
        if(abs(h)<tol): break
    print("newton_horner: x0=%g; x=%g, in %d iterations" %(x0,x,it))
    return x,it





def arrayfunction(row, col): 

    array = [] 
    for i in range(row):
        rowarray = []
        for j in range(col):
            rowarray.append([row * i + j])
        array.append(rowarray)
    return array

def whileloopdiv (): 
    d = 1
    c = 0
    while (d > 10**-6):
       d = d/2
       c = c + 1
    print(c)
    return c

def findmax ():
    randnum = []
    maxnum = 0
    for i in range (0,20):
        num = random.randint(0,20)
        randnum.append(num)
    print(randnum)
    for j in randnum[1:]:
        if j > maxnum:
            maxnum = j
    print(maxnum)
    return (randnum)

def plotfunction ():
    coeff = [2, -5, -11, 20, 10]
    P = np.poly1d(coeff)
    Pder = np.polyder(P)
    Proots = np.roots(P)
    x = np.linspace(-3,4,5)
    y = P
    plt.plot(x, y)
    plt.show()
    print("This is the root", Proots)

    plt.plot(x, y,newton_horner(coeff,3,10**(-12),1000),'r--', Proots, 'bs') 

    plt.show()

    
    




def main ():
    array = arrayfunction(5,5)
    print("This is the 5x5 matrix")
    print(array)
    print("This is the while loop")
    whileloopdiv()
    print("This is the max function")
    findmax()
    print("This is the plot function")
    plotfunction()
    
    
main ()