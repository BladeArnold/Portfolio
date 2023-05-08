import numpy as np; import numpy.linalg as la
import pandas as pd; import seaborn as sbn;
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn import datasets; #print(dir(datasets))
np.set_printoptions(suppress=True)
import time

from synthetic_data import *; from util_KNN import *

# Generate synthetic data
DATA = synthetic_data()
X = DATA[:,:-1]; y = DATA[:,-1]
N,d = X.shape; nclass = len(set(y))
print(' nclass = %d; (N, d) = (%d, %d)' %(nclass,N,d))

# Denoise data using KNN
Xd, yd = data_denoise(X,y,0.9)

# Visualize original and denoised data using KNN
dataCellipses(X, y, 'fort-synthetic2-KNNMVEE.png')
dataCellipses(Xd,yd,'fort-synthetic2-KNNMVEE-DN.png')
