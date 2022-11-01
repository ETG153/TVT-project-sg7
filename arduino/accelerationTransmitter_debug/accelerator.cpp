#include "accelerator.h"
#include <Wire.h>

// MMA8452Q I2C address is 0x1C(28)
#define Addr 0x1C

Accelerator::Accelerator() {
  Serial.println("Accelerator created!");
  Wire.begin();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x2A);
  // StandBy mode
  Wire.write(0x00);
  // End I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x2A);
  // Active mode
  Wire.write(0x01);
  // End I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x0E);
  // Set range to +/- 2g
  Wire.write(0x00);
  // End I2C Transmission
  Wire.endTransmission();
  delay(300);
}


Accelerator::~Accelerator() {
  Wire.end();
  Serial.println("Accelerator deleted!");
}

void Accelerator::makeMeasurement() {

}

Measurement Accelerator::getMeasurement() {

}
