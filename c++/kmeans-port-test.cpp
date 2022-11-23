
#include <iostream>
#include <math.h>

using namespace std;

struct point_s {
    int x, y, z;
};

//  Prototypes
int kMeansEvaluate(const point_s testpoint, const point_s* centroids, int k);
int getDistance(point_s pointA, point_s pointB);

//  Initial global variables
const int centroids_int[][3] = {
    //   X     Y     Z
    {1985, 3084, 2080},
    {2015, 1951, 1041},
    {1969, 1023, 1995},
    {1021, 2087, 2045},
    {3051, 2080, 2082},
    {2059, 2014, 3082} };

//  Main program
int main() {
    const int k = sizeof(centroids_int) / sizeof(centroids_int[0]);
    point_s centroids[k];
    point_s testpoint;

    cout << "K: " << k << '\n';

    // Copy center point values to structs
    for (int i = 0; i < k; i++) {
        centroids[i].x = centroids_int[i][0];
        centroids[i].y = centroids_int[i][1];
        centroids[i].z = centroids_int[i][2];
        cout << "Centroid " << i << " X: " << centroids[i].x << " Y: " << centroids[i].y << " Z: " << centroids[i].z << '\n';
    }

    // Get point to be evaluated from user
    cout << "Enter test point coordinates' X value: ";
    cin >> testpoint.x;
    cout << "Enter test point coordinates' Y value: ";
    cin >> testpoint.y;
    cout << "Enter test point coordinates' Z value: ";
    cin >> testpoint.z;
    cout << "\nTest point coordinates (XYZ): " << testpoint.x << ' ' << testpoint.y << ' ' << testpoint.z << "\n\n";

    // Evaluate the point and print result
    int closestIndex = kMeansEvaluate(testpoint, centroids, k);
    cout << "\nCentroid " << closestIndex << " is closest\n";
}

// Definitions

int kMeansEvaluate(const point_s testpoint, const point_s* centroids, int k) {
    unsigned int lowestDistance = -1; // Initialize at maximum integer value
    int closestIndex;

    for (int i = 0; i < k; i++) {
        int distance = getDistance(testpoint, centroids[i]);
        cout << "Distance to centroid " << i << ": " << distance << '\n';
        if (distance < lowestDistance) {
            lowestDistance = distance;
            closestIndex = i;
        }
    }

    return closestIndex;
}

int getDistance(const point_s pointA, const point_s pointB) {
    return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2) + pow(pointA.z - pointB.z, 2));
}
