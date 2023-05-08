import numpy as np; import numpy.linalg as la
import matplotlib.pyplot as plt; import seaborn as sbn
from numpy import diag,dot
from matplotlib.patches import Ellipse
from scipy.linalg import svd
import math
from SYNTH_SETTINGS import *; from util_fig import *;
import warnings; warnings.filterwarnings("ignore")
from sklearn.neighbors import NearestNeighbors

def class_center(X,y):
    """ compute the class centers: dim=(c,d)"""
    CC = []
    for c in range(len(set(y))):
        CC.append(list(np.mean(X[y==c],axis=0)))
    return np.array(CC)

def VT2angle(VT):
    return math.acos(np.abs(VT[0,0])) *(180/np.pi);

def aniso_dist2(Xc,s,VT,C):
    """ Measure anisotropic distances for data points in a class """
    AD2 = []
    N,d = Xc.shape
    for i in range(N):
         AD2.append( sum(((Xc[i]-C).dot(VT[j])/s[j])**2 for j in range(d)) )
    return np.array(AD2)

def dataCellipses(X, y, savename, k=5):
    N,d = X.shape; nclass = len(set(y))
    if k >= N:  # Check k is not greater than the number of samples
        k = N-1
    if d==2:  #for figures
        ELL = [];
        #fig, p = plt.subplots()  #Open new plots
        p = plt.subplot(111)      #Reuse instances
    for c in range(nclass):
        Xc = X[y==c]; CC = np.mean(Xc,axis=0)

        # Compute k-NN distances
        neigh = NearestNeighbors(n_neighbors=k+1)
        neigh.fit(Xc)
        _, indices = neigh.kneighbors(Xc)
        indices = indices[1:] # exclude self as neighbor
        knn_X = Xc[indices]

        # Compute covariance matrix
        cov_mat = np.zeros((d,d))
        for i in range(len(Xc)):
            diff = knn_X[i-1]-CC
            cov_mat += diff.reshape(1,-1) @ diff.reshape(-1,1)
        cov_mat /= len(Xc)-1
        # Compute eigenvalues and eigenvectors
        eigvals, eigvecs = np.linalg.eig(cov_mat)
        angle = math.atan2(eigvecs[1,0], eigvecs[0,0]) * (180/np.pi)
        eta = np.sqrt(eigvals)*2

        if d==2:  #for figures
            plt.scatter(Xc[:,0],Xc[:,1],s=15,c=COLOR[c],marker=MARKER[c])
            ELL.append(Ellipse(CC, eta[0], eta[1], angle ) )

    if d==2:  #for figures
        for c, e in enumerate(ELL):
            e.set_clip_box(p.bbox); e.set_alpha(0.33)
            e.set_facecolor(COLOR[c])
            p.add_artist(e)
        plt.title('KNN-Denoising')
        myfigsave(savename)
        plt.show(block=False); plt.pause(5)




def data_denoise(X, y, rpick, k=5):
    N, d = X.shape
    nclass = len(set(y))
    for c in range(nclass):
        Xc = X[y == c]
        y1 = y[y == c]
        CC = np.mean(Xc, axis=0)

        # Compute k-NN distances
        neighor = NearestNeighbors(n_neighbors=k)
        neighor.fit(Xc)
        dists, indices = neighor.kneighbors(Xc)

        # Compute weights based on distances
        weights = 1.0 / (dists + 1e-6)

        # Denoise data
        denoised_Xc = np.zeros_like(Xc)
        for i in range(Xc.shape[0]):
            wsum = np.sum(weights[i])
            denoised_Xc[i] = np.sum(Xc[indices[i]] * weights[i].reshape(-1, 1), axis=0) / wsum

        # Pick top rpick fraction of denoised data
        npick = round(Xc.shape[0] * rpick)
        sort_index = np.argsort(np.linalg.norm(denoised_Xc - CC, axis=1))
        if c == 0:
            Xout = denoised_Xc[sort_index[:npick]]
            yout = y1[sort_index[:npick]]
        else:
            Xout = np.row_stack((Xout, denoised_Xc[sort_index[:npick]]))
            yout = np.row_stack((yout, y1[sort_index[:npick]]))
    return Xout, yout.reshape(len(Xout))






