
#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#define USE_SERIAL

#include "messaging.h"

struct measurement_s
{
  unsigned int x;
  unsigned int y;
  unsigned int z;
};

class Accelerator
{
  public:
    Accelerator();
    ~Accelerator();
    void makeMeasurement();
    measurement_s getMeasurement();

  private:
    measurement_s m;
    void sensorStart();
    void sensorStop();
};

#endif // ACCELERATOR_H
