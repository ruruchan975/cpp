import numpy as np

data_dir = "./mertoncollege1/"

points2D = []
for i in range(3):
    points2D.append(np.loadtxt(data_dir + "2d/00" + str(i+1) + ".corners").T)

for i in range(3):
    print(points2D[i])

points3D = np.loadtxt(data_dir + "3d/p3d").T

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

