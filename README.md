# TVT-project-sg7
TVT21SPL Autumn 2022 application project

## Project description
In this project an Arduino development board (devboard), an accelerometer, a Raspberry Pi, and a Python TCP client will be used to train a machine learning algorithm.
Once this algorithm is trained, it will be ported to C++ and run on the Arduino devboard with the accelerometer attached.

## Setup
### Arduino
Initially the Arduino will be connected both to an accelerometer and an RF transceiver.
It will read values from the accelerometer, and then transmit them to the Raspberry Pi.
The data will be transmitted through the RF transceiver using the `RadioHead` library developed by Airspayce Pty Ltd.
Once the algorithm has been trained by the transmitted data, the RF transceiver will no longer be needed.

### Raspberry Pi
This part of the project has been set up by the teacher(s), and consists of a Raspberry Pi with an RF transceiver attached.
Its purpose is to function as an IoT router, storing the received accelerometer data in an internal MySQL database.
The database's contents can be read by a computer over TCP with a HTTP API.

### TCP client
The client will be written in Python, and operated on the student's laptop.
The data read by the client will then be parsed and prepared for use for machine learning.
