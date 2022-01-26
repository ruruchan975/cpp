import numpy as np
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import axes3d, Axes3D

data_dir = "./mertoncollege1/"

points2D = []
for i in range(3):
    points2D.append(np.loadtxt(data_dir + "2d/00" + str(i+1) + ".corners").T)

for i in range(3):
    print("points2D, " + str(i) + " =")
    print(points2D[i])

points3D = np.loadtxt(data_dir + "3d/p3d").T

print("points3D = ")
print(points3D)

corr = np.genfromtxt(data_dir + "2d/nview-corners", dtype="int", missing_values="*")

print("corr =")
print(corr)

# 3x4 camera projection matrix, one per image.
camera_projection_matrix = []
for i in range(3):
    camera_projection_matrix.append(np.loadtxt(data_dir + "2d/00" + str(i+1) + ".P"))

for i in range(3):
    print(camera_projection_matrix[i])

X = np.vstack( (points3D, np.ones(points3D.shape[1])) )
print("X = ")
print(X)

def project(P, x3d):
    x2d = np.dot(P, x3d)
    print("before x2d = ")
    print(x2d)
    for i in range(3):
        x2d[i] /= x2d[2]
    print("after x2d = ")
    print(x2d)
    return x2d

x = project(camera_projection_matrix[0], X)

plt.figure()
plt.plot(points2D[0][0], points2D[0][1], "*")

plt.figure()
plt.plot(x[0], x[1], "r.")

#fig = plt.figure()
#ax = fig.gca(projection='3d')
#ax.plot(points3D[0], points3D[1], points3D[2], "k.")

# get index no 
ndx = (corr[:,0] >= 0) & (corr[:,1] >= 0)
print("ndx =")
print(ndx)

x1 = points2D[0][:,corr[ndx,0]]
x1 = np.vstack((x1, np.ones(x1.shape[1])))
x2 = points2D[1][:,corr[ndx,1]]
x2 = np.vstack((x2, np.ones(x2.shape[1])))

def compute_fundamental(x1, x2):
    n = x1.shape[1]
    if x2.shape[1] != n:
        raise ValueError("Error")
    
    A = np.zeros((n,9))
    for i in range(n):
        A[i] =[
            x1[0,i] * x2[0,i],
            x1[0,i] * x2[1,i],
            x1[0,i] * x2[2,i],
            x1[1,i] * x2[0,i],
            x1[1,i] * x2[1,i],
            x1[1,i] * x2[2,i],
            x1[2,i] * x2[0,i],
            x1[2,i] * x2[1,i],
            x1[2,i] * x2[2,i]
        ]
    
    U,S,V = np.linalg.svd(A)
    F = V[-1].reshape(3,3)

    U,S,V = np.linalg.svd(F)
    S[2] = 0
    F = np.dot(U, np.dot(np.diag(S), V))

    return F




F = compute_fundamental(x1, x2)
print("F =")
print(F)



plt.show()


