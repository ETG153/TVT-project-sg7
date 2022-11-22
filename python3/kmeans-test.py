import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

filepath = "data.csv"

rawdata = pd.read_csv(filepath)
acceldata = pd.DataFrame(rawdata, columns=["accelX", "accelY", "accelZ"]).to_numpy()
#rowcount = len(acceldata.index)
maxval = np.amax(np.amax(acceldata))
minval = np.amin(np.amin(acceldata))
#print("Row count: " + str(rowcount))

centerpoints = np.random.randint(low=minval, high=maxval, size=(6,3))   # Coordinates for each center point
distances = np.zeros(6)             # The distance of a given point to each center point
hitcounts = np.zeros(6)             # How many times each center point has been the closest (or 'hit')
centerpointsums = np.zeros((6,3))   # The cumulative coordinates of each hit
print(centerpoints)

# Calculate which data points are closest to which center points
for eachpoint in acceldata:
    for eachcenter in centerpoints:
        distances[np.where(centerpoints == eachcenter)[0]] = int(np.linalg.norm(eachcenter - eachpoint))
    closestindex = np.where(distances == np.amin(distances))
    centerpointsums[closestindex] += eachpoint
    print(centerpointsums[closestindex])
    print(eachpoint)
    hitcounts[closestindex] += 1

oldcenters = np.copy(centerpoints)

for eachcenter in centerpoints:
    centerindex = np.where(centerpoints == eachcenter)[0][0]
    print(hitcounts[centerindex])
    print(centerpointsums[centerindex])
    if (hitcounts[centerindex] == 0):
        centerpoints[centerindex] = np.random.randint(low=minval, high=maxval, size=(3))
    else:
        centerpoints[centerindex] = centerpointsums[centerindex] / hitcounts[centerindex]

figure = plt.figure()
plot = figure.add_subplot(projection="3d")
plot.set_xlabel("X")
plot.set_ylabel("Y")
plot.set_zlabel("Z")

plot.scatter(oldcenters[:,0], oldcenters[:,1], oldcenters[:,2], color="b",marker="+", alpha=0.9)
plot.scatter(centerpoints[:,0], centerpoints[:,1], centerpoints[:,2], color="g",marker="*", alpha=1)
plot.scatter(acceldata[:,0], acceldata[:,1], acceldata[:,2], color="r",marker="o", alpha=0.5)

plt.show()
