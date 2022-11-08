
#include "messaging.h"
#include "accelerator.h"

uint8_t NumberOfMeasurements = 0;
uint8_t orientationFlag = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop() {
  NumberOfMeasurements = 0;
  orientationFlag = 0;

  Serial.println("Enter measurement count");
  while (NumberOfMeasurements == 0) {
    if (Serial.available() > 0) {
      NumberOfMeasurements = Serial.parseInt();
    }
  }

  Serial.println("What's up? (X/x, Y/y, Z/z)");
  while (orientationFlag != 'X' && orientationFlag != 'x' && orientationFlag != 'Y' && orientationFlag != 'y' && orientationFlag != 'Z' && orientationFlag != 'z') {
    if (Serial.available() > 0) {
      orientationFlag = Serial.read();
    }
  }

  Accelerator accel;
  Messaging rf;

  for (int M = 0; M < NumberOfMeasurements; M++) {
    const uint8_t id = M;

    accel.makeMeasurement();
    measurement_s measurement = accel.getMeasurement();
    rf.createMessage(measurement);

    if (rf.sendMessage(id, orientationFlag)) {
      Serial.println("Successfull transmission");
      if (rf.receiveACK()) {
        Serial.println("Receiver got message, going to next measurement");
      } else {
        Serial.println("Reciver did not get the message. Need to resend it");
        M--;  // Let's just rewind for loop
      }
    } else {
      Serial.println("Transmission fails");
    }
  }
}
