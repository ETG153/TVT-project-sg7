
#include "messaging.h"
#include "accelerator.h"

const uint8_t flags = 0xff;

void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop() {
  Serial.println("Enter measurement count");
  int NumberOfMeasurements = 0;
  while (NumberOfMeasurements == 0) {
    if (Serial.available() > 0) {
      NumberOfMeasurements = Serial.parseInt();
    }
  }

  Accelerator accel;
  Messaging rf;

  for (int M = 0; M < NumberOfMeasurements; M++) {
    const uint8_t id = M;

    accel.makeMeasurement();
    measurement_s measurement = accel.getMeasurement();
    rf.createMessage(measurement);

    if (rf.sendMessage(id, flags)) {
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
