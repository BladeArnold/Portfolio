import numpy as np; import pandas as pd
import seaborn as sbn; import matplotlib.pyplot as plt
import time
from sklearn.model_selection import train_test_split
from sklearn import datasets; #print(dir(datasets))
import warnings
warnings.filterwarnings('ignore')
np.set_printoptions(suppress=True)


class mcless:
    def __init__(self, threshold=0.5, learning_rate=0.01, num_epochs=100):
        self.threshold = threshold
        self.learning_rate = learning_rate
        self.num_epochs = num_epochs
        
    def fit(self, X, y):
        N = X.shape[0]
        A = np.column_stack((np.ones([N,]), X)) 
        num_classes = len(np.unique(y))
        B = np.zeros([N,num_classes]) 
        num_features = X.shape[1]
        self.weights = np.zeros([num_features + 1, num_classes])
        
        for c in range(num_classes):
            y_c = np.zeros_like(y)
            y_c[y == c] = 1
            for epoch in range(self.num_epochs):
                net_inputs = np.dot(A, self.weights[:,c])
                activations = self.activation(net_inputs)
                errors = y_c - activations
                gradient = np.dot(A.T, errors)
                self.weights[:,c] += self.learning_rate * gradient

        ATA = np.dot(A.T, A)
        ATB = np.dot(A.T, B)
        W = np.dot(np.linalg.inv(ATA), ATB)

        
    def predict(self, X):
        N = X.shape[0]
        Atest = np.column_stack((np.ones([N,]), X))
        P = np.dot(Atest, self.weights)
        self.activation(P)
        prediction = np.argmax(P, axis=1);
        return prediction
    
    def score(self, X, y):
        y_pred = self.predict(X)
        return np.mean(y_pred == y)
    
    def activation(self, z):
        return 1 / (1 + np.exp(-z))


#=====================================================================
# DATA: Read & Preprocessing
# load_iris, load_wine, load_breast_cancer, ...
#=====================================================================
# data_read = datasets.load_iris(); #print(data_read.keys())
data_read = datasets.load_wine(); #print(data_read.keys())
# data_read = pd.read_csv('synthetic1.data', header=None, encoding='utf-8');
# data_read = pd.read_csv('synthetic2.data', header=None, encoding='utf-8');


#synthethic data features 
#must have this to use the pd.read comment out the others to use this one 
# N = data_read.shape[0]
# X = data_read.iloc[:, :-1]
# y = data_read.iloc[:, -1]
# A = np.column_stack((np.ones([N,]), X))
# dataname = 'synthetic2.data'
# targets = np.unique(y)
# features = np.array([f'feature_{i+1}' for i in range(X.shape[1])])


X = data_read.data
y = data_read.target
# dataname = data_read.filename
targets = data_read.target_names
features = data_read.feature_names

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
        X, y, test_size=rtest, random_state=it, stratify = y)
    model = mcless()
    model.fit(Xtrain, ytrain)
    ##clf = myCLF(Xtrain,ytrain); clf.fit(); ## My classifier
    Acc[it] = model.score(Xtest, ytest)
#-----------------------------------------------
# Print: Accuracy && E-time
#-----------------------------------------------
etime = time.time()-btime
# print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
#         %(dataname,np.mean(Acc)*100,np.std(Acc)*100,etime/run))
print(' %s: Acc.(mean,std) = (%.2f,%.2f)%%; Average E-time= %.5f'
        %("Wine",np.mean(Acc)*100,np.std(Acc)*100,etime/run))

predctions = model.predict(Xtest)

# Print the predictions
print("Predictions:")
print(predctions)
#=====================================================================
# Scikit-learn Classifiers, for Comparisions
#=====================================================================
exec(open("sklearn_classifiers.py").read())

