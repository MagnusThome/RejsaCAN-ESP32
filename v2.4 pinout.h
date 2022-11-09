// Pinout v2.4

#define FORCE_ON    25
#define SENSE_V_DIG 14
#define SENSE_V_ANA 35

#define BLUE_LED    13
#define YELLOW_LED  12

#define CAN_RX      16
#define CAN_TX      17
#define CAN_WAKEUP	4

#define HI_DRIVER   27    // 3V3 high driver power output

#define SDA         21    // I2C 
#define SCL         22    // I2C

#define SPI_MISO    19    // SPI
#define SPI_MOSI    23    // SPI
#define SPI_CLK     18    // SPI
#define SPI_SS      5     // SPI chip select for SD card reader or other off board auxiliaries 

#define KLINE_RX	34
#define KLINE_TX	32

/*
Also available on the row of pads:

GPIO33  General GPIO, no default use
GPIO26  General GPIO, no default use

*/





/*

Total list of available solderable breakout pads are:

GPIO21  or I2C SDA
GPIO22  or I2C SCL

GPIO18  or SPI CLK
GPIO23  or SPI MOSI
GPIO19  or SPI MISO
GPIO5   or SPI SS

GPIO33  General GPIO, no default use
GPIO26  General GPIO, no default use
GPIO27  Power output driver, not actual GPIO pin

GPIO12  LED only, no pad!
GPIO13  LED only, no pad!


*/
