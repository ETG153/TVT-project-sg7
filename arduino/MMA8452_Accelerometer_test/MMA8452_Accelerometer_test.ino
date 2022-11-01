
#include <Wire.h>

// MMA8452Q I2C address is 0x1C(28)
#define Addr 0x1C

byte data[7];

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 115200
  Serial.begin(115200);
  Serial.println("init");

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x2A);
  // StandBy mode
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x2A);
  // Active mode
  Wire.write(0x01);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x0E);
  // Set range to +/- 2g
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop() {
  // Request 7 bytes of data
  Wire.requestFrom(Addr, 7);

  // Read 7 bytes of data
  // status, xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
  if (Wire.available() == 7)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
  }

  // Convert the data to 12-bit format
  int xAccl = ((data[1] * 256) + data[2]) / 16;
  if (xAccl > 2047)
  {
    xAccl -= 4096;
  }

  int yAccl = ((data[3] * 256) + data[4]) / 16;
  if (yAccl > 2047)
  {
    yAccl -= 4096;
  }

  int zAccl = ((data[5] * 256) + data[6]) / 16;
  if (zAccl > 2047)
  {
    zAccl -= 4096;
  }

  // Output data to serial monitor
  Serial.print("Acceleration in X-Axis : ");
  Serial.print((float)xAccl / 1000 * 9.81);
  Serial.println(" m/s2");
  Serial.print("Acceleration in Y-Axis : ");
  Serial.print((float)yAccl / 1000 * 9.81);
  Serial.println(" m/s2");
  Serial.print("Acceleration in Z-Axis : ");
  Serial.print((float)zAccl / 1000 * 9.81);
  Serial.println(" m/s2");
  Serial.println();
  delay(500);
}
