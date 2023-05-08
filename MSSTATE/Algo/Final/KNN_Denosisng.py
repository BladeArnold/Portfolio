#---------------------------------------------------------------
import numpy as np; np.set_printoptions(suppress=True)
import pandas as pd
import seaborn as sbn; import matplotlib.pyplot as plt
import time
from scipy.linalg import svd
import math
from SYNTH_SETTINGS import *; from util_fig import *
from sklearn.model_selection import train_test_split
from sklearn import datasets; #print(dir(datasets))
from matplotlib.patches import Ellipse
from sklearn.neighbors import KNeighborsClassifier
import warnings; warnings.filterwarnings("ignore")


#=====================================================================
# DATA: Read & Preprocessing
# load_iris, load_wine, load_breast_cancer, ...
#=====================================================================
# data_read = datasets.load_iris(); #print(data_read.keys())
# data_read = datasets.load_wine(); #print(data_read.keys())
data_read = pd.read_csv('synthetic1.data', header=None, encoding='utf-8');
# data_read = pd.read_csv('synthetic2.data', header=None, encoding='utf-8');


#synthethic data features 
#must have this to use the pd.read comment out the others to use this one 
N = data_read.shape[0]
X = data_read.iloc[:, :-1]
y = data_read.iloc[:, -1]
A = np.column_stack((np.ones([N,]), X))
dataname = 'synthetic1.data'
targets = np.unique(y)
features = np.array([f'feature_{i+1}' for i in range(X.shape[1])])


# X = data_read.data
# y = data_read.target
# # dataname = data_read.filename
# targets = data_read.target_names
# features = data_read.feature_names







#----------------------------------
def conf_count(neigh,y):
    cscore = np.zeros(y.shape)
    for i in range(len(y)):
        labels = y[neigh[i]]
        cscore[i] = len(labels[labels==y[i]])
    return cscore



#-- Parameters for KNN ------------
k=5; xi=4;

#-- KNN, with "kneighbors" --------
KNN = KNeighborsClassifier(n_neighbors=k);
KNN.fit(X,y)

neigh = KNN.kneighbors(X, return_distance=False)
print('Kneighbors:\n',neigh)

#-- Confidence score --------------
cscore = conf_count(neigh,y)
print('Confidence Score:\n',cscore)
xi -= 0.1;
Xd = X[cscore>=xi]
yd = y[cscore>=xi]
print('Denoised Data (Xd,yd):\n',np.column_stack((Xd,yd)))


print('X.shape=',X.shape, 'y.shape=',y.shape)
#---------------------------------------------------------------------
# SETTING
#---------------------------------------------------------------------
N,d = X.shape; labelset=set(y)
nclass=len(labelset);
print('N,d,nclass=',N,d,nclass)

rtrain = 0.7e0; run = 100
rtest = 1-rtrain

#=====================================================================
# CLASSIFICATION
#=====================================================================
btime = time.time()
Acc = np.zeros([run,1])


for it in range(run):
    Xtrain, Xtest, ytrain, ytest = train_test_split(
        X, y, test_size=rtest, random_state=it, stratify=y)
    
    KNN.fit(Xtrain, ytrain)
    Acc[it] = np.mean(KNN.predict(Xtest)[0] == ytest)
#-----------------------------------------------
# Print: Accuracy && E-time
#-----------------------------------------------
etime = time.time()-btime
print("KNN with denosing")
print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
        %(dataname,np.mean(Acc)*100,np.std(Acc)*100,etime/run))
# print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
#         %("Wine",np.mean(Acc)*100,np.std(Acc)*100,etime/run))

predctions = KNN.predict(Xtest)

# Print the predictions
print("Predictions:")
print(predctions)

#=====================================================================
# Scikit-learn Classifiers, for Comparisions
#=====================================================================
exec(open("sklearn_classifiers.py").read())