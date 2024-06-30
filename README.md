# Mbed OS Ethernet MAC driver for the ENC28J60 

This Arduino library uses [ENC28J60 driver](https://github.com/njh/EtherSia/tree/main/src) by Nicholas Humfrey with  adaptation from the esp8266 lwIP_enc28j60 library.

Wire a ENC28J60 module to standard SPI pins of the board. On Nano pins 10 to 13. On Portenta pins 8, 9, 10 and SC pin 7. On Giga R1 use the SPI header and pin 10 as CS. 

Arduino Giga should work with the [HW-270 shield](https://github.com/Networking-for-Arduino/EthernetENC/wiki/Shields).

For Arduino Giga R1, the Ethernet library has to be copied from Mbed Portenta boards package. For Mbed Core Nano boards and RP2040 boards, Ethernet and SocketWrapper library have to be copied.

To use the driver include it in the sketch with the Portenta Ethernet library:

```
#include <ENC28J60EMAC.h>
#include <PortentaEthernet.h>
``````
