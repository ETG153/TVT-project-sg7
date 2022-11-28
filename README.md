# TVT-project-sg7
TVT21SPL Autumn 2022 application project

![Project architecture diagram](documentation/Project-architecture.jpg)

## Project description
In this project an Arduino development board (devboard), an accelerometer, a Raspberry Pi, and a Python TCP client will be used to train a machine learning algorithm.
Once this algorithm is trained, it will be ported to C++ and run on the Arduino devboard with the accelerometer attached.

## Setup
### Arduino
Initially the Arduino will be connected both to an accelerometer and an RF transceiver.
It will read values from the accelerometer, and then transmit them to the Raspberry Pi.
The data will be transmitted through the RF transceiver using the `RadioHead` library developed by Airspayce Pty Ltd.
Once the algorithm has been trained by the transmitted data, the RF transceiver will no longer be needed.

### Raspberry Pi
This part of the project has been set up by the teacher(s), and consists of a Raspberry Pi with an RF transceiver attached.
Its purpose is to function as an IoT router, storing the received accelerometer data in an internal MySQL database.
The database's contents can be read by a computer over TCP with a HTTP API.

### TCP client
The client will be written in Python, and operated on the student's laptop.
The data read by the client will then be parsed and prepared for use for machine learning.

## K-means algorithm explained
The algorithm's purpose is to find the centroid (arithmetic mean of data points) in each cluster. In this situation, there is one cluster for each axis from the "center" (2048, 2048, 2048). These are -X, +X, -Y, +Y, -Z, and +Z. Around each one of these centroids is a cluster of data points, each representing one measurement made by the Arduino setup.

The algorithm works as follows:
### Step 1:
The source data is imported and formatted to a useful format:

![Scatter plot of formatted data set](documentation/scatterplot-rawdata.png)

### Step 2:
The algorithm generates K random centroids, where K is the desired centroid count. In this case we know there are 6, so we will generate 6 centroids.

![Scatter plot with randomized centroids](documentation/scatterplot-randomcenters.png)

### Step 3:
With each iteration the randomized centroids get closer to the true centroids of each cluster.

![Scatter plot with once iterated centroids and their starting points](documentation/scatterplot-oneiteration.png)

### Step 4:
The previous step is repeated until the centroids' coordinates do not change, at which point we have the finished centroids.

![Scatter plot of finished algorithm](documentation/scatterplot-iterated.png)
