# RejsaCAN

RejsaCAN is an ESP32 based board aimed at car use that I put together for my own use in my assorted crazy car projects. The board has an on board CAN interface and can be powered directly from the car (5-26V). It also includes the option to auto shutdown so not to drain the car battery.

There is no bespoke code for the board apart from pin definitions, it's just a piece of universal hardware, but by using easy to use open source Arduino libraries it can be made to interface not only to various CAN buses, Network/Wifi and Bluetooth but to numerous sensors and other peripherals using the ESP32's built in interfaces.

If you think the board really would fit your project you can give me a holler at magnust@gmail.com. I had JLCPCB make and assemble my own small batch of boards.

<!--img src=pics/3dcad.png align=right width=38%-->
<img src=pics/3dcad.png>

## ESP32 interfaces

- SPI bus
- I2C bus
- BLE (Bluetooth 4.2)
- Wifi (both as AP or client)
- Numerous TCP/IP standards (everything from simple http, mqtt, ajax, ntp to running a full webserver on it with a user interface)
- USB port (serial in/out)
- Analog input, PWM or analog output

## Examples

- Read CAN data and send back CAN packets to control the car (set to sport mode as default, lock doors when driving away, this is one of my current projects)
- CAN to BLE or network/Wifi bridge
- CAN interface for sniffing CAN bus with for example Savvycan
- Read I2C/SPI/analog sensor data and write to CAN bus for CAN bus based data loggers
- Publish live telemetric data on internet from Racechrono (I'm starting this project now) 
- Drive alarm beeper or LED to show status of CAN data (like my small project Money Shift Saver)
- Drive high power peripherals using a driver board
- Translate CAN data between two CAN buses (like my small project Current Gear HUD here on github)

## Ideas for peripherals

- A second CAN port (MCP2515 board)
- IR camera sensor arrays (MLX90xxx or AMG8833) to log tire, brake, drivetrain temperatures over BLE to Racechrono or CAN based loggers (like my project RejsaRubberTrac)
- Laser based TOF distance sensor to log suspension travel (I did this too with RejsaRubberTrac) 
- SPI or I2C based color displays to show CAN bus data like IC intake or oil temps or alarms
- SPI or I2C based color displays to show live telemetric data fetched over BLE from Racechrono
- Driver board to drive high power items
- Step motor drivers
- Multiple input analog or digital boards

# Functionality

## Auto shutdown

When the engine is running and charging the car battery the incoming voltage used to power the board is a little bit higher than when the engine is stopped. This can be used to automate starting the board and shutting it down completely, so not to drain the car battery.

The board reads the incoming power voltage in two ways:

- Using an ADC in the ESP32 the voltage powering the board can be read and monitored in your code

- As default the on board DC-DC circuit converting incoming voltage to 3,3V will shutdown the whole board when the incoming power voltage drops down to "car is parked, battery isn't charging" and restart the board when the voltage increases to "car is started, battery is charging". This can be disabled by a small modification on the board so it always runs (down to 5V).

In addition to the above, once the board is running you can programmatically force it to keep running even if the power voltage drops due to the engine being turned off. This is done by pulling a pin high so you can for example keep the board running during a pit stop or a red light even if the car engine temporarily shuts down.

## CAN interface

Using the ESP32's built in CAN driver and an on board CAN transceiver chip with a CAN termination resistor you can hook up the board straight to the car's OBD2 port or attach it directly on any CAN bus. You just need to connect the four wires. 12V power, ground, CAN high and low.

More CAN ports can be added using the readily available and cheap MCP2515 boards.

## Three on board LEDs  

The board has two LEDs that are controlled by pins on the ESP32. This can be used for anything, like indicating Wifi/BLE being connected, errors or whatnot. 

There is also a third LED that indicates that the board is powered on.

## Schematics

<img src=pics/schematic_v2.1.png>

## Connecting the board

I've used a widely available OBD2 splitter cable (flat cable) that has one male and two female connectors. I hook up the male connector to the car, cut off one female connector and wire the remaining pig tail cable into the RejsaCAN board and one female connector is then free for other equipment to hook up to the car.

Picture showing what wires to use but please measure your cable and don't trust all these splitter cables are 100% identical. (the second female splitter connector is not visible in pic)

<img src=pics/OBD2%20splitter%20pinout.jpg>
