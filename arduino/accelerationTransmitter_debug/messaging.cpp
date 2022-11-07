#include "messaging.h"
#include "accelerator.h"

//#define DEBUGGING

Messaging::Messaging() {
  Serial.println("messaging created!");
  pmanager = new RHReliableDatagram(driver, TRANSMITTER_ADDRESS);

  if (!pmanager->init())
    Serial.println("Radiohead manager init failed");

}

Messaging::~Messaging() {
  Serial.println("Messaging deleted!");
  delete pmanager;
}

void Messaging::createMessage(measurement_s m) {
  //memcpy(data, &m, 6);
  data[0] = m.x >> 8;
  data[1] = m.x & 0xFF;
  data[2] = m.y >> 8;
  data[3] = m.y & 0xFF;
  data[4] = m.z >> 8;
  data[5] = m.z & 0xFF;
  messageLength = 6;
}

bool Messaging::sendMessage(uint8_t id, uint8_t flags) {
#ifdef DEBUGGING
  Serial.print("Sending values ");
  Serial.print((int)(data[0] << 8) + data[1]);
  Serial.print(" ");
  Serial.print((int)(data[2] << 8) + data[3]);
  Serial.print(" ");
  Serial.println((int)(data[4] << 8) + data[5]);
#else
  unsigned long start = millis();
  unsigned long timeout = millis() - start;
  while (timeout < 500)
  {
    timeout = millis() - start;
  }
  driver.setModeTx();
  const uint8_t to = RECEIVER_ADDRESS;
  const uint8_t from = TRANSMITTER_ADDRESS;

  pmanager->setHeaderTo(to);
  pmanager->setHeaderFrom(from);
  pmanager->setHeaderId(id);
  pmanager->setHeaderFlags(flags);

  bool returnValue = false;

  if (pmanager->sendto(data, messageLength, RECEIVER_ADDRESS))
  {
    returnValue = true;
  }
  pmanager->waitPacketSent();
  return returnValue;
#endif
}

bool Messaging::receiveACK() {
  driver.setModeRx();
  unsigned long start = millis();
  unsigned long timeout = millis() - start;
  bool receiverResult = false;
  uint8_t to;
  uint8_t from;
  uint8_t len;
  uint8_t id;
  uint8_t flags;
  while ((timeout < 1500) && (!pmanager->available()))
  {
    timeout = millis() - start;
  }

  // Jos while luupista päästään, niin on saatu ACK tai on kulunut 1s
  receiverResult = pmanager->recvfrom(buf, &len, &from, &to, &id, &flags);
  if (receiverResult)
  {
    Serial.println("ACK received");
    Serial.println((char *)buf);
    Serial.print("Sent from address $");
    Serial.println(from, HEX);
    Serial.print("ID: ");
    Serial.println(id);
    Serial.print("Flags: ");
    Serial.println(flags);
    return true;
  }
  else
  {
    Serial.println("ACK not received, retransmit");
    return false;
  }

}
