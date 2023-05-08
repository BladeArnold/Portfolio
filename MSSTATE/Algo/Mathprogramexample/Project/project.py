
from synthetic_data import *; from util_PCA import *
import warnings
warnings.filterwarnings('ignore')
np.set_printoptions(suppress=True)


from collections import Counter



class myKNN:
    def __init__(self, k, confidence, distance_metric='euclidean'):
        self.k = k
        self.confidence = confidence
        self.distance_metric = distance_metric

    def fit(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X_test):
        predictions = []
        confidences = []
        for x in X_test:
            # Calculate distances from x to all training samples
            if self.distance_metric == 'euclidean':
                distances = np.sqrt(np.sum((self.X_train - x)**2, axis=1))
            elif self.distance_metric == 'manhattan':
                distances = np.sum(np.abs(self.X_train - x), axis=1)
            elif self.distance_metric == 'cosine':
                dot_products = np.dot(self.X_train, x)
                norms = np.linalg.norm(self.X_train, axis=1) * np.linalg.norm(x)
                distances = 1 - dot_products / norms
            
            # Find k nearest neighbors
            nearest_indices = np.argsort(distances)[:self.k]
            nearest_labels = self.y_train[nearest_indices]
            
            # Assign class label by majority vote
            most_common = Counter(nearest_labels).most_common(1)
            predictions.append(most_common[0][0])
            
            # Calculate confidence region
            same_class_neighbors = nearest_labels[nearest_labels == most_common[0][0]]
            if len(same_class_neighbors) >= self.confidence:
                confidences.append(1)
            else:
                confidences.append(0)
        
        return predictions, confidences




class myPCA:
    
    def __init__(self, X, k):
        self.X = X
        self.k = k
    
    def compute(self):
        # Compute covariance matrix
        cov = np.cov(self.X.T)

        # Compute eigenvalues and eigenvectors
        eigvals, eigvecs = np.linalg.eig(cov)

        # Sort eigenvectors in descending order of eigenvalues
        idx = np.argsort(eigvals)[::-1]
        eigvals = eigvals[idx]
        eigvecs = eigvecs[:, idx]

        # Truncate eigenvectors to keep k principal components
        Wk = eigvecs[:, :self.k]

        # Compute truncated score matrix
        Zk = np.dot(self.X, Wk)

        return Zk, Wk



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
        X, y, test_size=rtest, random_state=it, stratify=y)
    model = myKNN(5, 4)
    model.fit(Xtrain, ytrain)
    Acc[it] = np.mean(model.predict(Xtest)[0] == ytest)
#-----------------------------------------------
# Print: Accuracy && E-time
#-----------------------------------------------
etime = time.time()-btime
print("KNN without denosing")
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