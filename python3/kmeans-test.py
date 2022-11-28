import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from datetime import datetime as dt

sourcefile = "data.csv"
outputfile = "kmeans-results.csv"

maxiterations = 1000

rawdata = pd.read_csv(sourcefile)
acceldata = pd.DataFrame(rawdata, columns=["accelX", "accelY", "accelZ"]).to_numpy()
maxval = np.amax(np.amax(acceldata))
minval = np.amin(np.amin(acceldata))

centerpoints = np.random.randint(low=minval, high=maxval, size=(6,3))   # Coordinates for each center point
prevcenterpoints = np.zeros_like(centerpoints)                          # Coordinates of previous center points
prevcenters = []                     # List of center points from previous iterations
distances = np.zeros(6)             # The distance of a given point to each center point
hitcounts = np.zeros(6)             # How many times each center point has been the closest (or 'hit')
prevhitcounts = np.zeros(6)          # Hit counts from previous iteration
centerpointsums = np.zeros((6,3))   # The cumulative coordinates of each hit

starttime = dt.now()
# Run the algorithm for n iterations or until no changes occur
for iteration in range(maxiterations):
    print("Iteration " + str(iteration))

    # Copy hit counts from previous iteration and reset cumulative variables
    prevcenterpoints = np.copy(centerpoints)
    hitcounts = np.zeros(6)
    centerpointsums = np.zeros((6,3))

    # Calculate which data points are closest to which center points
    for eachpoint in acceldata:
        for eachcenter in centerpoints:
            distances[np.where(centerpoints == eachcenter)[0]] = int(np.linalg.norm(eachcenter - eachpoint))
        closestindex = np.where(distances == np.amin(distances))
        centerpointsums[closestindex] += eachpoint
        hitcounts[closestindex] += 1

    prevcenters.append(np.copy(centerpoints))

    for eachcenter in centerpoints:
        centerindex = np.where(centerpoints == eachcenter)[0][0]
        if (hitcounts[centerindex] == 0):
            centerpoints[centerindex] = np.random.randint(low=minval, high=maxval, size=(3))
        else:
            centerpoints[centerindex] = centerpointsums[centerindex] / hitcounts[centerindex]
    
    # Check if there was no change in hitcounts
    if np.array_equal(centerpoints, prevcenterpoints):
        print("No more movement, exiting")
        break
    else:
        print("Changes made, running again")

stoptime = dt.now()

if not np.array_equal(centerpoints, prevcenterpoints):
    print("Max iterations reached")

print("Ran for " + str(stoptime-starttime))
print("Final center points:")
outputdf = pd.DataFrame(centerpoints, columns=["X", "Y", "Z"])
print(outputdf)
outputdf.to_csv(outputfile)

figure = plt.figure()
plot = figure.add_subplot(projection="3d")
plot.set_xlabel("X")
plot.set_ylabel("Y")
plot.set_zlabel("Z")

for each in prevcenters:
    plot.scatter(each[:,0], each[:,1], each[:,2], color="b",marker="+", alpha=0.25, zorder=1)
plot.scatter(centerpoints[:,0], centerpoints[:,1], centerpoints[:,2], color="g",marker="*", alpha=1, zorder=0)
plot.scatter(acceldata[:,0], acceldata[:,1], acceldata[:,2], color="r",marker="o", alpha=0.05, zorder=2)

plt.show()
