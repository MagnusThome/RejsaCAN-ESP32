// Pinout v6.0



// Shortlist of all GPIO accessible on pin header / solder pads
#define GPIO1   1     // no default use
#define GPIO4   4     // SPI bus MTMS/CS SD_CARD.   Used by SD card slot. Free to use for anything if SD card slot isn't used
#define GPIO5   5     // Shared SPI bus MTDI/MISO.  Used by SD card slot. Free to use for anything if SD card slot isn't used
#define GPIO6   6     // Shared SPI bus MTCK/CLOCK. Used by SD card slot. Free to use for anything if SD card slot isn't used 
#define GPIO7   7     // Shared SPI bus MTDO/MOSI.  Used by SD card slot. Free to use for anything if SD card slot isn't used 
#define GPIO14  14    // no default use
#define GPIO15  15    // no default use
#define GPIO16  16    // Serial TXD or free to use for anything if serial port isn't used
#define GPIO17  17    // Serial RXD or free to use for anything if serial port isn't used



// GPIO for CAN
#define CAN0_RX       23
#define CAN0_TX       3
#define CAN1_RX       20
#define CAN1_TX       21


// OUTPUT HIGH = CAN low power mode (listen only)
// OUTPUT LOW = CAN high speed mode
// High impedance (INPUT) = CAN slope control mode
#define CAN0_RS       2
#define CAN1_RS       22  


// GPIO for extra serial port
#define SERIAL_TXD    16
#define SERIAL_RXD    17


// GPIO for SPI bus (shared with SD card slot)
#define MTDI          5
#define MTCK          6
#define MTDO          7
#define SD_CARD       4


// GPIO for other on board hardware
#define FORCE_ON      18   // Set high to keep board running even when the power voltage drops below 13.5V when the engine isn't running/charging battery
#define SENSE_V_ANA   0    // For measuring the incoming power voltage (detect discharge level, health of battery, if engine is running or not....)
#define POWER_LED     19   // To lower power consumption when in sleep set to OUTPUT LOW to turn off and *disable* the power led. Or control the green power LED on/off while board is running
#define RGB_LED       8    // WS2812C LED
#define BOOT_BUTTON   9    // Can be used *after* boot as a universal button






