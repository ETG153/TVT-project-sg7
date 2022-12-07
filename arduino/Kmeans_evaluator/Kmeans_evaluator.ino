
#include "accelerator.h"
#include "KmeansEval.h"

#define BTN_PIN 12
#define BTN_PRESSED (digitalRead(BTN_PIN) == LOW)

//#define VERBOSE

const int centroids[][3] = {
  {1985, 3084, 2080},
  {2015, 1951, 1041},
  {1969, 1023, 1995},
  {1021, 2087, 2045},
  {3051, 2080, 2082},
  {2059, 2014, 3082}
};

const int k = sizeof(centroids) / sizeof(centroids[0]);

char centroidAxis[k];

EvaluateK kmeans(k, centroids);

void setup() {
  Serial.begin(115200);
  delay(500);
#ifdef VERBOSE
  Serial.println();
  Serial.println("### Ported K-means evaluator ###");
#endif

  pinMode(BTN_PIN, INPUT_PULLUP);

#ifdef VERBOSE
  Serial.println("Assigning axis...");
#endif
  assignAxis(k, centroidAxis);
}

void loop() {
#ifdef VERBOSE
  Serial.println();
  Serial.println("Awaiting input");
#endif
  while (!BTN_PRESSED)
    delay(100);
#ifdef VERBOSE
  Serial.println("Button pressed!");
#endif
  while (BTN_PRESSED)
    delay(100);
#ifdef VERBOSE
  Serial.println("Button released!");

  Serial.println("Making measurement...");
#endif

  for (byte i = 0; i < 25; i++) {

    Accelerator accel;
    accel.makeMeasurement();
    measurement_s measurement = accel.getMeasurement();
    point_s testpoint;
    testpoint.x = measurement.x;
    testpoint.y = measurement.y;
    testpoint.z = measurement.z;
    const int result = kmeans.evaluate(testpoint);

#ifdef VERBOSE
    Serial.print("Result: Axis currently pointed up is ");
    switch (centroidAxis[result]) {
      case 'x':
        Serial.println("negative X");
        break;

      case 'y':
        Serial.println("negative Y");
        break;

      case 'z':
        Serial.println("negative Z");
        break;

      case 'X':
        Serial.println("positive X");
        break;

      case 'Y':
        Serial.println("positive Y");
        break;

      case 'Z':
        Serial.println("positive Z");
        break;

    }
#else
    Serial.println(centroidAxis[result]);
    delay(250);
#endif
  }
}

void assignAxis(const int _k, char* _centroidAxis) {
  for (int i = 0; i < _k; i++) {
    point_s testpoint;
    testpoint.x = 0x07FF;
    testpoint.y = 0x07FF;
    testpoint.z = 0x07FF;
    char axis;

    switch (i) {
      case 0:
        testpoint.x = 0x0000;
        axis = 'x';
        break;

      case 1:
        testpoint.x = 0x0FFF;
        axis = 'X';
        break;

      case 2:
        testpoint.y = 0x0000;
        axis = 'y';
        break;

      case 3:
        testpoint.y = 0x0FFF;
        axis = 'Y';
        break;

      case 4:
        testpoint.z = 0x0000;
        axis = 'z';
        break;

      case 5:
        testpoint.z = 0x0FFF;
        axis = 'Z';
        break;

    }
    _centroidAxis[kmeans.evaluate(testpoint)] = axis;
  }
}
