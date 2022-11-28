
#include "KmeansEval.h"
#include <math.h>

EvaluateK::EvaluateK(const int k, int centroids[][3]): _k(k) {
  // Copy center point values to structs
  for (int i = 0; i < _k; i++) {
    _centroids[i].x = centroids[i][0];
    _centroids[i].y = centroids[i][1];
    _centroids[i].z = centroids[i][2];
  }
}

EvaluateK::~EvaluateK() {

}

int EvaluateK::evaluate(const point_s testpoint) {
    unsigned int lowestDistance = -1; // Initialize at maximum integer value
    int closestIndex;

    for (int i = 0; i < _k; i++) {
        unsigned int distance = getDistance(testpoint, _centroids[i]);
        if (distance < lowestDistance) {
            lowestDistance = distance;
            closestIndex = i;
        }
    }

    return closestIndex;
}

unsigned int EvaluateK::getDistance(const point_s pointA, const point_s pointB) {
  return sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2) + pow(pointA.z - pointB.z, 2));
}
