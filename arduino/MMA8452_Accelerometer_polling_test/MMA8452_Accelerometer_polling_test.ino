
#include <Wire.h>

// MMA8452Q I2C address is 0x1C(28)
#define Addr 0x1C

byte data[7];
int xAccl, yAccl, zAccl;

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 115200
  Serial.begin(115200);
  Serial.println("init");

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 1
  Wire.write(0x2A);
  // Standby mode (reset register)
  Wire.write(0x00);
  // Subsequent write to control register 2:
  // Enable high resolution oversampling
  Wire.write(0b00010010);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x0E);
  // Set range to +/- 2G
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
}

void loop() {
  sensorStart();
  Wire.requestFrom(Addr, 7);
  while (Wire.available() < 7)
    delay(10);
  // Read 7 bytes of data
  /* Data order:
     Status
     xAccl LSB
     xAccl MSB
     yAccl LSB
     yAccl MSB
     zAccl LSB
     zAccl MSB
  */

  for (byte i = 0; i < 6; i++) {
    data[i] = Wire.read();
  }

  sensorStop();

  // Convert the data to 12-bit format
  xAccl = ((data[1] * 256) + data[2]) / 16;
  if (xAccl > 2047)
  {
    xAccl -= 4096;
  }

  yAccl = ((data[3] * 256) + data[4]) / 16;
  if (yAccl > 2047)
  {
    yAccl -= 4096;
  }

  zAccl = ((data[5] * 256) + data[6]) / 16;
  if (zAccl > 2047)
  {
    zAccl -= 4096;
  }

  // Output data to serial monitor
  Serial.print("Acceleration in X-Axis : ");
  Serial.print(xAccl);
  Serial.println(" mG");
  Serial.print("Acceleration in Y-Axis : ");
  Serial.print(yAccl);
  Serial.println(" mG");
  Serial.print("Acceleration in Z-Axis : ");
  Serial.print(zAccl);
  Serial.println(" mG");
  Serial.println();
  delay(1000);
}

void sensorStart() {
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

void sensorStop() {
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
