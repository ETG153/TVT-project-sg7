
#include <RH_ASK.h>
#include <RHReliableDatagram.h>

#define CLIENT_ADDRESS 0x01
#define SERVER_ADDRESS 0x02

#define DATA_SPEED 2000
#define RX_PIN 11
#define TX_PIN 12
#define SDN_PIN 10
#define SDN_INVERTED false

RH_ASK driver(DATA_SPEED, RX_PIN, TX_PIN, SDN_PIN, SDN_INVERTED);

RHReliableDatagram manager(driver, CLIENT_ADDRESS);

uint8_t data[] = "Echo!";
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];

void setup() {
  delay(500);
  Serial.begin(115200);	  // Debugging only
  if (!driver.init())
    Serial.println("Driver init failed");
  else if (!manager.init())
    Serial.println("Manager init failed");
  else
    Serial.println("\n ### RH 2-way client initialized! ###");
}

void loop() {
  Serial.print("Sending message \"");
  Serial.print((char*) data);
  Serial.print("\"... ");
  if (manager.sendtoWait(data, sizeof(data), SERVER_ADDRESS)) {
    uint8_t len = sizeof(buf);
    uint8_t from;
    Serial.println("OK!");
    Serial.print("Awaiting response... ");
    if (manager.recvfromAckTimeout(buf, &len, 2000, &from)) {
      Serial.println("Received!");
      Serial.print("Response: \"");
      Serial.print((char*)buf);
      Serial.println("\"\n");
    } else {
      Serial.println("Response timed out!");
    }
  } else {
    Serial.println("Acknowledgement timed out!");
  }
  delay(500);
}
