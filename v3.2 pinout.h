// Pinout v3.2

#define FORCE_ON    17
#define SENSE_V_DIG 8
#define SENSE_V_ANA 9

#define BLUE_LED    10
#define YELLOW_LED  11

#define CAN_RX      13
#define CAN_TX      14
#define CAN_RS      38    // Standby and/or faster rise times (from v3.2 only)

#define HI_DRIVER   21    // 3V3 high driver power output

#define SDA         1     // I2C 
#define SCL         2     // I2C

#define MISO        41    // SPI
#define MOSI        40    // SPI
#define CLK         39    // SPI
#define SD_CARD     45    // SPI CS for SD card reader

/*

Total list of available solderable breakout pads are:

GPIO01  or I2C SDA
GPIO02  or I2C SCL
GPIO39  or SPI CLK
GPIO40  or SPI MOSI
GPIO41  or SPI MISO

GPIO12  no default use
GPIO48  no default use
GPIO47  no default use
GPIO21  Power output driver, not actual GPIO pin

GPIO10  LED only, no pad!
GPIO11  LED only, no pad!

Only available as pads on the rear side of the board:
  
GPIO06  extra
GPIO07  extra
GPIO15  extra
GPIO16  extra

RXD     second UART
TXD     second UART

GPIO0   and PROGR mode strapping pin
GPIO03  and JTAG_ENABLE strapping pin
GPIO42  or JTAG MTMS

*/
