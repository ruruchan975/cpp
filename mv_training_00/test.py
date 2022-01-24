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

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.plot(points3D[0], points3D[1], points3D[2], "k.")

plt.show()

