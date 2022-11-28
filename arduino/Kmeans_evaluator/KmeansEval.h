
#ifndef KMEANSEVAL_H
#define KMEANSEVAL_H

struct point_s {
  int x, y, z;
};

class EvaluateK {

  public:

    EvaluateK(const int k, int centroids[][3]);
    ~EvaluateK();
    int evaluate(const point_s testpoint);
    unsigned int getDistance(const point_s pointA, const point_s pointB);

  private:

    const int _k;
    point_s _centroids[];
};

#endif
