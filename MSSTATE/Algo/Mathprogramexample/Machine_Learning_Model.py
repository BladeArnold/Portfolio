import numpy as np; import pandas as pd
import seaborn as sbn; import matplotlib.pyplot as plt
import time
from sklearn.model_selection import train_test_split
from sklearn import datasets; #print(dir(datasets))
import warnings
warnings.filterwarnings('ignore')
np.set_printoptions(suppress=True)


#=====================================================================
# DATA: Read & Preprocessing
# load_iris, load_wine, load_breast_cancer, ...
#=====================================================================
data_read = pd.read_csv('synthetic1.data', header=None, encoding='utf-8'); #print(data_read.keys())
#data_read = pd.read_csv('synthetic2.data', header=None, encoding='utf-8'); #print(data_read.keys())
#data_read = datasets.load_iris(); #print(data_read.keys())
#data_read = datasets.load_wine(); #print(data_read.keys())


W = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])

#synthethic data features 
#must have this to use the pd.read comment out the others to use this one 
# N = data_read.shape[0]
# X = data_read.iloc[:, :-1]
# y = data_read.iloc[:, -1]
# A = np.column_stack((np.ones([N,]), X))
# dataname = 'synthetic2.data'
# targets = np.unique(y)
# features = np.array([f'feature_{i+1}' for i in range(X.shape[1])])


N = data_read.data.shape[0]
X = data_read.data
y = data_read.target
A = np.column_stack((np.ones([N,]), X))
#dataname = data_read.filename
dataname = data_read.DESCR
targets = data_read.target_names
features = data_read.feature_names

X = np.column_stack((np.ones([X.shape[0], 1]), X))

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
B = np.zeros([N,nclass])
from sklearn.neighbors import KNeighborsClassifier
clf = KNeighborsClassifier(5)
##from myCLF import myCLF ## My classifier


for it in range(run):
    Xtrain, Xtest, ytrain, ytest = train_test_split(X, y, test_size=rtest, random_state=it, stratify=y)

    Atrain = Xtrain
    
    clf = KNeighborsClassifier(n_neighbors=5)
    clf.fit(Atrain, ytrain)
    
    Btrain = np.zeros([ytrain.shape[0], nclass])
    
    
    A = np.vstack((A, Atrain))
    B = np.vstack((B, Btrain))
    
    Acc[it] = clf.score(Xtest, ytest)

    atest = Xtest[:, 1:]
    p = np.dot(atest, W)

    P = np.exp(p.reshape(-1, 1)) / np.sum(np.exp(p.reshape(-1, 1)), axis=0)

    prediction = np.argmax(P, axis=1) # predicted class labels
    

#-----------------------------------------------
# Print: Accuracy && E-time
#-----------------------------------------------
etime = time.time()-btime
print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
        %(dataname,np.mean(Acc)*100,np.std(Acc)*100,etime/run))
#=====================================================================
# Scikit-learn Classifiers, for Comparisions
#=====================================================================
exec(open("sklearn_classifiers.py").read())
