import numpy as np; import pandas as pd
import seaborn as sbn; import matplotlib.pyplot as plt
import time
import random 
from sympy import symbols, Eq
import math
from sklearn.model_selection import train_test_split
from sklearn import datasets;

#does the horner method on the input
def horner(A, x0):
    """ input: A = [a_n,...,a_1,a_0]
        output: p,d = P(x0),DP(x0) = horner(A,x0) """
    n = len(A)
    p = A[0]; d = 0

    for i in range(1,n):
        d = p + x0*d
        p = A[i] +x0*p
    return p,d

# finds the root of the polynomial
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




# uses for loops to print  of an 5x5 array
def arrayfunction(row, col): 

    array = [] 
    for i in range(row): #takes the row input and col input and ouputs numbers in each spot 
        rowarray = []
        for j in range(col):
            rowarray.append([row * i + j])
        array.append(rowarray)
    return array

# Shows how an while loop works in python while dividing.
def whileloopdiv (): 
    d = 1
    c = 0
    while (d > 10**-6):
       d = d/2
       c = c + 1
    print(c)
    return c

# finds the max in a set of numbers 
def findmax ():
    randnum = []
    maxnum = 0
    #makes a randoms numbers between 0 and 20
    for i in range (0,20): 
        num = random.randint(0,20)
        randnum.append(num)
    print(randnum)
    # looks for the max numbers 
    for j in randnum[1:]:
        if j > maxnum:
            maxnum = j
    print(maxnum)
    return (randnum)

# uses the np roots fucntion and the Newton method above to compare the outputs between to see which one is more accurte. 
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

    
    



# executes all the functions
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
