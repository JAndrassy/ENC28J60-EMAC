# Mbed OS Ethernet MAC (EMAC) driver for the ENC28J60 Ethernet controller
  and modules equipped with such chip.

This Arduino library has Mbed ENC28J60-EMAC driver from here: https://os.mbed.com/users/hudakz/code/ENC28J60-EMAC/. Only difference is a major fix of `ENC28J60_EMAC::link_out` and added `using namespace` required for ArduinoMbed-core.

The library is not extensively tested. It was created for now as proof of concept for external Mbed EMAC driver with ArduinoMbed-Core. Only Nano 33 BLE was tested.

To use it with Mbed Nano boards Ethernet library and SocketWrapper have to be copied from Mbed Portenta boards package. For Giga R1, Ethernet library has to be copied.

Two small fixes are required in Mbed-core libraries:
* in SocketWrapper library https://github.com/arduino/ArduinoCore-mbed/pull/747/files
* in Ethernet library https://github.com/arduino/ArduinoCore-mbed/pull/748/files

Wire the ENC28J60 module to standard SPI pins of the board. On Nano pins 10 to 13, on Giga R1 use the SPI header.

The Nano ENC28J60 Ethernet shield can be used with the 3.3V Nanos but only with [5 V level shifter removed!](https://github.com/JAndrassy/EthernetENC/wiki/Nano-Ethernet-Shield)

Next to board.txt create boards.local.txt with a line for your board, to define the SPI pins as Mbed PinName. Example for Nano 33 BLE:
```
nano33ble.build.extra_flags=-DENC28J60_MOSI=p1 -DENC28J60_MISO=p8 -DENC28J60_SCK=p13 -DENC28J60_CS=p2
``` 
