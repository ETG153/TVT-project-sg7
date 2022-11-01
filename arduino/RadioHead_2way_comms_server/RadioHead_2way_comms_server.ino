
#include <RH_ASK.h>
#include <RHReliableDatagram.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

#define DATA_SPEED 2000
#define RX_PIN 11
#define TX_PIN 12
#define SDN_PIN 10
#define SDN_INVERTED false

RH_ASK driver(DATA_SPEED, RX_PIN, TX_PIN, SDN_PIN, SDN_INVERTED);
RHReliableDatagram manager(driver, SERVER_ADDRESS);

uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];

void setup() {
  delay(500);
  Serial.begin(115200);	  // Debugging only
  if (!driver.init())
    Serial.println("Driver init failed");
  else if (!manager.init())
    Serial.println("Manager init failed");
  else
    Serial.println("\n ### RH 2-way server initialized! ###");
}

void loop() {
  if (manager.available())
  {
    uint8_t len = sizeof(buf);
    uint8_t from = 0;
    if (manager.recvfromAck(buf, &len, &from))
    {
      Serial.print("Transmission received  from $");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println((char*)buf);

      Serial.print("Returning message to sender... ");
      if (manager.sendtoWait(buf, sizeof(buf), from))
        Serial.println(" OK!");
      else
        Serial.println(" Acknowledgement timed out!");
      Serial.println();
    }
  }
}
