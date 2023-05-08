import numpy as np
import pandas as pd; import seaborn as sbn;
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn import datasets; #print(dir(datasets))
np.set_printoptions(suppress=True)
import time

from synthetic_data import *; from util_PCA import *


#-------------------------------------------------------
# DATA = synthetic_data()
# X = DATA[:,:-1]; y = DATA[:,-1]
# N,d = X.shape; nclass = len(set(y))
# dataname = 'synthetic1.data'
# print(' nclass = %d; (N, d) = (%d, %d)' %(nclass,N,d))

# #-------------------------------------------------------







#=====================================================================
# DATA: Read & Preprocessing
# load_iris, load_wine, load_breast_cancer, ...
#=====================================================================
data_read = datasets.load_iris(); #print(data_read.keys())
# data_read = datasets.load_wine(); #print(data_read.keys())




X = data_read.data
y = data_read.target
dataname = data_read.filename
targets = data_read.target_names
features = data_read.feature_names








rtrain = 0.7e0; run = 100
rtest = 1-rtrain

#=====================================================================
# CLASSIFICATION
#=====================================================================

btime = time.time()
Acc = np.zeros([run,1])
Xd, yd = data_denoise(X,y,0.9)



# Train a logistic regression model
model = LogisticRegression()

for it in range(run):
    Xtrain, Xtest, ytrain, ytest = train_test_split(
        X, y, test_size=rtest, random_state=it, stratify=y)

    model.fit(Xtrain, ytrain)
    Acc[it] = np.mean(model.predict(Xtest)[0] == ytest)



# Test the model
y_pred = model.predict(Xtestpca)
#-----------------------------------------------
# Print: Accuracy && E-time
#-----------------------------------------------
etime = time.time()-btime
print("PCA with denoising")
print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
        %(dataname,np.mean(Acc)*100,np.std(Acc)*100,etime/run))
# print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
#         %("Wine",np.mean(Acc)*100,np.std(Acc)*100,etime/run))

predctions = model.predict(Xtest)

# Print the predictions
print("Predictions:")
print(predctions)

dataCellipses(X, y, 'fort-wine-MVEE.png')
#dataCellipses(Xd,yd,'fort-wine-MVEE-DN.png')

#=====================================================================
# Scikit-learn Classifiers, for Comparisions
#=====================================================================
exec(open("sklearn_classifiers.py").read())