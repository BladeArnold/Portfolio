#=====================================================================
# Required: X, y, [dataname, run]
print('========= Scikit-learn Classifiers, for Comparisions =========')
#=====================================================================
from sklearn.preprocessing import StandardScaler
from sklearn.datasets import make_moons, make_circles, make_classification
from sklearn.neural_network import MLPClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.gaussian_process import GaussianProcessClassifier
from sklearn.gaussian_process.kernels import RBF
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis
#from sklearn.inspection import DecisionBoundaryDisplay

#-----------------------------------------------
classifiers = [
    LogisticRegression(max_iter = 1000),
    KNeighborsClassifier(5),
    SVC(gamma=2, C=1),
    RandomForestClassifier(max_depth=5, n_estimators=50, max_features=1),
   
]
names = [
    "Logistic Regr",
    "KNeighbors-5 ",
    "RBF SVM ",
    "Random Forest",

]
#-----------------------------------------------
if "Wine" == None: dataname = 'No-dataname';
if run is None: run = 100;

#===============================================
import os; acc_max=0
for name, clf in zip(names, classifiers):
    Acc = np.zeros([run,1])
    btime = time.time()

    for it in range(run):
        Xtrain, Xtest, ytrain, ytest = train_test_split(
            X, y, test_size=rtest, random_state=it, stratify = y)

        clf.fit(Xtrain, ytrain);
        Acc[it] = clf.score(Xtest, ytest)

    etime = time.time()-btime
    accmean = np.mean(Acc)*100
    print('%s: %s: Acc.(mean,std) = (%.2f,%.2f)%%; E-time= %.5f'
        %(os.path.basename("Data"),name,accmean,np.std(Acc)*100,etime/run))
    if accmean>acc_max:
        acc_max= accmean; algname = name
print('sklearn classifiers max: %s= %.2f' %(algname,acc_max))