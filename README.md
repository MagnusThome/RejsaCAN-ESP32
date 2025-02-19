# RejsaCAN

RejsaCAN is a 3x5 centimetre small ESP32 or ESP32-S3 based board aimed at car use that I put together for my own use in my assorted crazy car projects. The board has an onboard CAN interface and can be powered directly from the car (5-24V). It also includes the option to auto shutdown so not to drain the car battery. This is especially important if you have it plugged in to a car OBD2 connector since these always supply constant 12V power to the connector, even when the car is parked and turned off.

There is no bespoke code for the board apart from pin definitions, it's just a piece of universal hardware, but by using easy to use open source Arduino libraries it can be made to interface not only to various CAN buses, Network/Wifi and Bluetooth but to numerous sensors and other peripherals using the ESP32's built in interfaces.

You can assemble your own board if you want, you find schematics, Gerber files and bill of materials in the <a href=Schematics>schematics folder</a>. I currently don't make any boards but if you need factory assembled boards in quantitites you can always contact me at magnust@gmail.com and we can discuss and see.
  
### Nice review and get started guide at cnx-software  
  
https://www.cnx-software.com/2023/05/12/rejsacan-esp32-s3-can-bus-board-arduino-car-hacking/  
  
### Navigate  
  
- <a href=./>Main page (this page)</a>  
 
- <a href=Projects%20and%20ideas>Fun projects and ideas</a>  
 
- <a href=Schematics>Schematics</a>

- <a href=Code%20Examples>Code examples</a>
 
- <a href=Tips%20to%20setup%20IDE%20and%20get%20started>Links to some different CAN libraries and tips to get started</a>  
  
-  <a href=3dprint>Examples of 3D printable housings</a>  

-  <a href=Auxiliary%20boards>Some odd auxiliary boards I made to mount an OBD2 connector, display, thermal cam...</a>  

<hr>
  
![IMG_20221009_144837](https://user-images.githubusercontent.com/32169384/194758017-36f51c68-5326-45f4-9183-615ad204baf5.jpg)

   
## Pinout  
  
See complete pinout.h 
  
ESP32    https://github.com/MagnusThome/RejsaCAN-ESP32/blob/main/v2.4%20pinout.h  
ESP32-S3 https://github.com/MagnusThome/RejsaCAN-ESP32/blob/main/v3.2%20pinout.h  

![S3 rear](https://github.com/MagnusThome/RejsaCAN-ESP32/assets/32169384/c748ce53-0b77-4376-b636-6cdc1cb92bef)
   
  
## Schematics

click to get full schematics

<a href=https://github.com/MagnusThome/RejsaCAN-ESP32/tree/main/Schematics><img src=https://github.com/MagnusThome/RejsaCAN-ESP32/assets/32169384/1679f1cd-1905-4c42-a11c-f8b68e32965e></a>

## The board is based around an ESP32 or ESP32-S3 chip

The ESP32-S3 is a very nice and capable chip that supports a mind boggling range of different communication standards and hardware auxiliaries making it a very versatile "hub" for shuffling data between different systems.  

- SPI bus
- I2C bus
- BLE (Bluetooth 5)
- Wifi (both as AP or client)
- Networking, everything from simple http, mqtt, ajax, ntp to running a full webserver on it with a user interface
- USB port (serial in/out and also OTG as virtual keyboard, wireless storage...)
- Analog input, PWM or analog output

## Examples

- Read CAN data and send back CAN packets to control the car (set to sport mode as default, lock doors when driving away, this is one of my current projects)
- CAN to BLE or network/Wifi bridge
- CAN interface for sniffing CAN bus with for example SavvyCAN
- Read I2C/SPI/analog sensor data and write to CAN bus for CAN bus based data loggers
- Publish live telemetric data on internet from Racechrono (I'm starting this project now)
- Drive alarm beeper or LED to show status of CAN data (like my small project Money Shift Saver and also low oil pressure warning)
- Drive high power peripherals using a driver board
- Translate CAN data between two CAN buses (like my small project Current Gear HUD here on github)

- I have already made a connector board to attach the RejsaCAN on the back of the commonly available small ILI9341 touch screen.

## Ideas for peripherals

<a target=_blank href=https://github.com/MagnusThome/RejsaRubberTrac><img align=right width=50% src=https://user-images.githubusercontent.com/32169384/195158064-2a3aa449-2554-4737-a2f2-7ac039983e5e.png></a>

- IR camera sensor arrays (MLX90xxx or AMG8833) to log tire, brake, drivetrain temperatures over BLE to Racechrono or CAN based loggers (like my project RejsaRubberTrac https://github.com/MagnusThome/RejsaRubberTrac)  
- Laser based TOF distance sensor to log suspension travel (I did this too with RejsaRubberTrac)  
- SPI or I2C based color displays to show CAN bus data like IC intake or oil temps or alarms  
- SPI or I2C based color displays to show live telemetric data fetched over BLE from Racechrono  
- A second CAN port  
- Driver board to drive high power items  
- Step motor drivers  
- Multiple input analog or digital boards  
   
## One of the 3D printed housings with OBD2 connector I've made
![IMG_20211116_203136](https://user-images.githubusercontent.com/32169384/142067937-3678866e-b6aa-4547-876a-56e76185f119.jpg)
 
 
## Or just the board and screw terminals
![IMG_20211116_202642](https://user-images.githubusercontent.com/32169384/142052421-174120e8-17d9-403a-9424-e6581dac0180.jpg)

# CAN interface

You can hook the board up straight to the car's OBD2 port or attach it directly to any CAN bus. You just need to connect the four wires. 12V power, ground, CAN high and low. There is of course a bus termination resistor on the board, it can be disabled if not needed by cutting a pcb trace and optionally mounting a pin header and jumper.

# Functionality

The idea was to make an as small as possible CAN + ESP32 board with as many cool and useful "good to have" functions as possible included. You know as well as I do that when tinkering around you suddenly get a new idea and need x or y :-D 

## Auto shutdown

When the engine is running and charging the car battery the incoming voltage used to power the board is a little bit higher than when the engine is stopped. This can be used to automate board shutdown so not to drain the car battery. As default the on board DC-DC power circuit will shutdown the whole board when the power voltage is below the "engine is running" threshold and boot up the board when it is above. But you can run the board in a number of other ways too, for example using ESP32 sleep mode, waking it and putting it to sleep depending on CAN traffic, voltage level from the car, delays and so on.

- An output (FORCE_ON GPIO17) can be pulled high to keep the board running even if the car voltage drops below the threshold (instead of disabling the auto shutdown fully on the pcb). The ESP32 can keep this pin high even during sleep.

- A digital input (SENSE_V_DIG GPIO08) monitors if the car voltage is above or below the "engine running" threshold. This can both be used to trigger waking the board from sleep or just as a simple check if the engine is charging the car battery or not.  

- The voltage from the car can be monitored using analog input (SENSE_V_ANA GPIO9) to check not only charging level but also battery discharge level when parked, health of charging, health of battery, detect large loads being switched on or off in the car and so on.

- The CAN data input (CAN_RX GPIO13) can also be used to trigger waking up the board from sleep as soon as CAN traffic is detected.

   
Either one can just let the board turn on and off with the auto shutdown hardware circuitry straight out of the box or you can run it in combination with software. For example, when the car voltage rises and the board boots you can pull FORCE_ON high to make sure the board keeps running even if there is a drop of voltage, for example due to red light start/stop functionality in the car or modern cars turning down battery charging even when driving. Then you just monitor either the threshold with SENSE_V_DIG or set your own thresholds using SENSE_V_ANA and then add your own timer delays or whatever. And of course, you can use CAN to check if the car is stopped in a multitude of ways, rpm, speed, gear...

### Fine tuning on/off voltage thresholds  

If your car has a more modern battery type than the old acid/led type or if it does the battery charging slightly different you might want to adjust the on/off voltage thresholds. If you keep R5 as 33k and adjust R4 you can get these switch-on and -off voltages:

| **R4** | **Turn on at** | **Turn off at** |
|-------:|---------------:|----------------:|
| 91k    | 13,7V           | 13,0V            |
| 90k    | 13,6V           | 12,9V            |
| 89k    | 13,5V           | 12,8V            |
| 88k    | 13,4V           | 12,7V            |
| 87k    | 14,3V           | 12,6V            |
| 86k    | 13,2V           | 12,5V            |
| 85k    | 13,1V           | 12,4V            |

  
### 24V vehicles

For 24V vehicles you can change the on/off voltage threshold by soldering on a resistor at the empty "ADJUST" position. I don't know what voltages one can expect in these vehicles while charging and not charging the battery so I have no idea what an appropriate resistor value should be there. 

   
![matrix power scenarios](https://user-images.githubusercontent.com/32169384/180321585-c3b46872-c4b4-4583-bcea-3c7e8c0705bd.gif)  

  


## "Good to haves"

### Three on board LEDs  

- Green power LED that shows if the board is turned on or not. If using the auto shutdown the green LED (and the board) will be turned on and off depending on if the car voltage is over or under the auto start/shutdown threshold.

- Blue LED to use for anything you fancy (BLUE_LED GPIO10) (this one is red on some boards due to the blue led being out of stock lately)
- Yellow LED to use for anything (YELLOW_LED GPIO11)

### Extra UART RX/TX

The ESP32-S3 has a built in USB port for uploading firmware, OTG support(!) and general communication. But on the board's rear there are breakout pads for a second UART (TXD0 and RXD0) so you can use this as a serial port and the board's USB port for other tasks like JTAG or OTG, acting as a peripheral keyboard, mouse, wireless storage and so on.

### 3V3 HIGH DRIVER

The GPIO pins on the ESP32-S3 can, in addition to general digital circuitry, also drive 10-20mA loads like LEDs and other smaller loads. But on the RejsaCAN board there is an added more powerful driver circuit that can drive slightly larger loads of a few hundred mA at 3,3V. This can be used for different things like powering external sensors or a small display that you want to be able to shutdown fully to minimize power consumption while in sleep mode for example. This 3V3_SWITCHED output is controlled by HI_DRIVER (GPIO21). The ESP32-S3 can keep this on or off when in sleep mode.

There is also a 3,3V power output pad in the row of connection pads on the board that is turned on whenever the board is running. Keep in mind that this is _not_ a 3V3 input to drive the board, it is only an output to drive external I2C, SPI and other sensors.

### SD card reader

The ESP32-S3 has an SD micro card reader on the rear of the pcb. It is connected to SPI and select SD_CARD (GPIO45)

### Other general IO pins
  
All the GPIOs found on the row of connector pads are general purpose. They can be PWM, analog, digital in/out whatever, special protocols driving or reading most things you can think of. But for ease of use for me with occasional lousy memory I have marked some default uses:  
  
I2C SDA  (GPIO1)  (A0)  
I2C SCL  (GPIO2)  (A1)  
GND  
3V3  
  
SPI MISO / MTDI  (GPIO41)  
SPI CLK  / MTCK  (GPIO39)  
SPI MOSI / MTDO  (GPIO40)  
  
General  (GPIO12)  
General  (GPIO48)  
General  (GPIO47)  
High driver switched output max 500mA  (GPIO21)  

On the rear side of the pcb you can get to a few extra pins but it's not possible to solder pin headers here due to the esp-module being on the other side of the board where these pads are.  
  
General  (GPIO6)  (A5)  
General  (GPIO7)  (A6)  
General  (GPIO15)  
General  (GPIO16)  
MTMS  (GPIO42)  
PROG  (GPIO0)  
JTAG_ENABLE  (GPIO3)  
TXD0   
RXD0  
  
  
### CAN bus

As mentioned earlier the CAN_RX (GPIO13) can wake the ESP32-S3 from sleep whenever any traffic is seen on the CAN bus.

To minimize power draw when not using the CAN bus, for example not listening to the bus to detect traffic to wake the ESP32 from sleep mode, the CAN transceiver can be put in standby mode by pulling CAN_RS (GPIO38) high. The ESP32-S3 can keep this pin high even when in sleep mode reducing the complete boards power draw to an absolute minimum.

The rise time of the CAN transceiver chip can be changed pulling CAN_RS (GPIO38) low. Default is keeping the pin unmodified in high impedance state for an optimal not-to-fast rise time setting. See specs for the transceiver chip SN65HVD230DR.

### JTAG

You can either run JTAG over the USB port or optionally keep the USB port free by connecting your JTAG hardware to MTDI, MTDO, MTCK and MTMS on the board. Note that MTMS is only available on the board's rear. The other are available in the row of connecting pads. Incidentally the MTDI, MTDO and MTCK are the same as the SPI default pins.

To enable JTAG mode you need to pull the JTAG_ENABLE pad, found on the rear of the board, high or low at boot.

### Board version

On v3.x boards you can programmatically check what version of the board your code is running on and adjust accordingly for the small changes that have been made on the boards. Set GPIO4 and GPIO5 to input pullup and check if the inputs are high or low.

- v3.1 = GPIO4 low and GPIO5 high  
- v3.2 = GPIO4 high and GPIO5 low  

### Changes

#### from v3.1 to v3.2

- Added RS control of the CAN chip to set both standby mode and faster rise times
- Added better over voltage protection on power from the car
- Upgraded over voltage protection on USB power
- Enabling ALWAYS_ON is now done by shorting two clearly marked pads on the rear of the board
- An added empty spot for resistor R19 ADJUST which can be added to lower the start/stop voltage threshold for the board
- For panic situations when you need more pins ;-) the GPIO6, GPIO7, GPIO15 and GPIO16 are available as unmarked pads but only on the rear of the board
  
#### From v2.3 to v.2.4
  
- Upgraded over voltage protection on USB power  

#### From v2.4 to v.2.5 and 3.2 to 3.3
  
- DC-DC converter supports 24V input. The auto switch on/off threshold can be changed by changing two resistor values.  

  
## Power consumption  
 
At 14V the complete board draws *on average* roughly:  
- Bluetooth turned on but no connections = 16mA (+ 4mA for power LED)
- Wifi turned on as AP with local web server but no connections = 46mA (+ 4mA for power LED)
- No wifi or Bluetooth = 14mA (+ 4mA for power LED)
- Sleep = 3mA (+ 4mA for power LED). Note that the CAN transceiver is fully active and the DC-DC buck converter probably has some idle draw also.
- Sleep and CAN transceiver put in standby = hmmm, must test this, a fraction of a mA is my guess.
   
## Housing

Check out 3D printable housings in the <a href=3dprint>the 3D-print directory</a>. So far I've made one housing where you connect using a cable and another one with an integrated OBD2 connector to plug directly into the car.

![4](https://user-images.githubusercontent.com/32169384/140327538-1fef4d27-3961-447a-bb28-ced90950dfcf.jpg)

![transparent-case-1](https://user-images.githubusercontent.com/32169384/140562825-fa751003-fabd-465a-9738-fe34dc1a9d12.jpg)

![small-housing(0)](https://user-images.githubusercontent.com/32169384/138956886-f83ddebf-1960-4e5f-990a-a6d5ac4cba14.jpg)
  
![IMG_20230926_152918](https://github.com/MagnusThome/RejsaCAN-ESP32/assets/32169384/d18ed917-d1ce-423b-a9eb-53d53fba226a)

 
## Connecting the board

When not using the housing with an integrated OBD2 connector or the screw terminals as seen in the picture above I've used a widely available OBD2 splitter cable (flat cable) that has one male and two female connectors. I hook up the male connector to the car, cut off one female connector and wire the remaining pig tail cable into the RejsaCAN board and one female connector is then free for other equipment to hook up to the car.

Picture showing what wires to use but please measure your cable and don't trust all these splitter cables to be 100% identical. (the second female splitter connector is not visible in pic)
   
![OBD2 splitter pinout](https://user-images.githubusercontent.com/32169384/180321794-e2e8f9a3-37a3-4594-a713-4c3d7f042926.jpg)
 
![small-housing(3)](https://user-images.githubusercontent.com/32169384/138956928-8b44a92c-3336-4f66-8bfb-3b2ae9432360.jpg)
 
![small-housing(2)](https://user-images.githubusercontent.com/32169384/138956945-97b0403a-e5a8-471f-bc6c-01ba239a281d.jpg)



