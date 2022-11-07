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
}


Accelerator::~Accelerator() {
  Wire.end();
  Serial.println("Accelerator deleted!");
}

void Accelerator::makeMeasurement() {
  byte data[7];

  sensorStart();
  Wire.requestFrom(Addr, 7);
  while (Wire.available() < 7)
    delay(10);

  for (byte i = 0; i < 6; i++) {
    data[i] = Wire.read();
  }

  sensorStop();

  // Convert the data to 12-bit format
  m.x = ((data[1] << 8) + data[2]) >> 4;
  m.x = m.x & 0x0FFF;

  m.y = ((data[3] << 8) + data[4]) >> 4;
  m.y = m.y & 0x0FFF;

  m.z = ((data[5] << 8) + data[6]) >> 4;
  m.y = m.y & 0x0FFF;
}

measurement_s Accelerator::getMeasurement() {
  return m;
}

void Accelerator::sensorStart() {
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 1
  Wire.write(0x2A);
  // Set ODR to 100 Hz
  // Enable reduced noise mode, 12-bit resolution, and active mode
  Wire.write(0b00011101);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(25);  // Wait for 2/ODR + 1 ms, + a little extra
}

void Accelerator::sensorStop() {
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 1
  Wire.write(0x2A);
  // Standby mode (reset register)
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  if (Wire.available()) {
    while (Wire.available()) {
      Wire.read();
    }
  }
}
