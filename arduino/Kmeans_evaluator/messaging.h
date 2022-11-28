#ifndef MESSAGING_H
#define MESSAGING_H

#define USE_SERIAL
#define TESTING

struct measurement_s;

#include <RHReliableDatagram.h>
#include <RH_ASK.h>

class Messaging {
  public:
    Messaging();
    ~Messaging();
    void createMessage(measurement_s m);
    bool sendMessage(uint8_t id, uint8_t flags);
    bool receiveACK();

  private:
#ifdef TESTING
    const uint8_t TRANSMITTER_ADDRESS = 5;
#else
    const uint8_t TRANSMITTER_ADDRESS = 56;
#endif
    const uint8_t RECEIVER_ADDRESS = 254;

    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t data[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t messageLength = 0;
    RH_ASK driver;
    RHReliableDatagram * pmanager;
};

#endif // MESSAGING_H
