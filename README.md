# ARDUINO_BAREMETAL
### Pre-requisite
1. Micorchip Studio 7.0
2. Windows 10/11 Operating System
3. ATMEGA 328p MCU or ARDUINO UNO Board
4. AVRDUDE

### Defination
The Porject deals with Baremetal Drivers for ATMEGA 328P series micro-controller. Currently it is only supporting UART in polling mode.

### How to compile
1. Go to Debug/, you will find Makefile, simply modify the path for the compiler as per your local development enviroment.
2. For configuring avrdude to flash binary in the MCU follow the following weblink for reference:
https://www.arnabkumardas.com/platforms/atmel/how-to-flash-or-program-arduino-from-atmel-studio/   
