## RejsaCAN

RejsaCAN is an ESP32 based board aimed at car use. It has an on board CAN interface and can be powered directly from the car (5-26V). It also includes the option to auto shutdown so not to drain the car battery.

Using available Arduino libraries it can be used to easily interface not only to various CAN buses but to numerous sensors and other periphals using the ESP32's built in interfaces.

- SPI bus
- I2C bus
- BLE (Bluetooth 4.2)
- Wifi (both as AP or client)
- Numerous TCP/IP standards (everything from simple http, mqtt, ajax, ntp to running a full webserver on it with a user interface)
- USB port (serial in/out)

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
- SPI or I2C based color displays to show live telemtric data fetched over BLE from Racechrono
