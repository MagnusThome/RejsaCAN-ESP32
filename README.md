# RejsaCAN

RejsaCAN is an ESP32 based board aimed at car use. It has an on board CAN interface and can be powered directly from the car (5-26V). It also includes the option to auto shutdown so not to drain the car battery.

Using available open source Arduino libraries it can be used to easily interface not only to various CAN buses, Network/Wifi and Bluetooth but to numerous sensors and other periphals using the ESP32's built in interfaces.

## ESP32 interfaces

- SPI bus
- I2C bus
- BLE (Bluetooth 4.2)
- Wifi (both as AP or client)
- Numerous TCP/IP standards (everything from simple http, mqtt, ajax, ntp to running a full webserver on it with a user interface)
- USB port (serial in/out)
- Analog inputs
- PWM or analog outputs

## Examples

- CAN to Wifi or BLE bridge
- CAN interface for sniffing CAN bus with for example Savvycan
- Read I2C/SPI/analog sensor data and write on CAN bus
- Publish live telemetric data on internet from Racechrono over BLE

## Ideas for peripherals

- A second CAN port (MCP2515 board)
- IR camera sensor arrays (MLX90xxx or AMG8833) to log tire, brake, drivetrain temperatures over BLE to Racechrono or CAN based loggers (see RejsaRubberTrac)
- Laser based TOF distance sensor to log suspension travel
- SPI or I2C based color displays to show CAN bus data like IC intake or oil temps
- SPI or I2C based color displays to show live telemetric data fetched over BLE from Racechrono

# Functinality

## Auto shutdown

When the engine is running and charging the car battery the incoming voltage used to power the board is a little bit higher than when the engine is stopped. This can be used to automate starting the board and shutting it down completely, so not to draing the car battery.

The board reads the incoming power voltage in two ways:

- Using an ADC in the ESP32 the voltage powering the board can be read and monitored in your code

- As default the on board DC-DC circuit converting incoming voltage to 3,3V will shutdown the whole board when the incoming power voltage drops down to "car is parked, battery isn't charging" and restart the board when the voltage increases to "car is started, battery is charging". This can be disabled by a small modification on the board so it always runs (down to 5V).

In addition to the above, once the board is running you can force to keep the board running even if the power voltage drops due to the engine being turned off. This is done by pulling a pin high so you can programatically keep the board running during a pit stop or a red light even if the car engine temporarily shuts down.

# ----
