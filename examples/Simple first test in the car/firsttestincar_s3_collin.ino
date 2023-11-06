/*

Good for an initial test in the car to check that the board and the car's OBD connector work as they should

- Blue LED blinks when CAN replies are received from the car
- Yellow LED is on when the engine rpm is over 2000 rpm

--------------------

Comment out everything about mcp2517fd and mcp2515 in the /esp32_can/src/ esp32_can.cpp and esp32_can.h library files

--------------------
*/

#define ESP32S3   // COMMENT THIS OUT FOR OLD ESP32 NON S3 BOARDS


#include "esp32_can.h"            // https://github.com/collin80/esp32_can AND https://github.com/collin80/can_common

#define CANPID_RPM          0x0C
#define CAN_REQST_ID        0x7DF 
#define CAN_REPLY_ID        0x7E8

#ifdef ESP32S3
  #define BLUE_LED      10
  #define YELLOW_LED    11
  #define RX_PIN        13
  #define TX_PIN        14
  #define CAN_RS        38
#else
  #define BLUE_LED      13
  #define YELLOW_LED    12
  #define RX_PIN        16
  #define TX_PIN        17
#endif


uint16_t rpm;


void setup() {
  Serial.begin(115200);
  Serial.println("Boot");

#ifdef ESP32S3
  Serial.setTxTimeoutMs(0); // prevent serial print delays if no usb
  pinMode(CAN_RS, OUTPUT);    // INPUT (high impedance) = slope control mode, OUTPUT = see next line
  digitalWrite(CAN_RS, LOW);  // LOW = high speed mode, HIGH = low power mode (listen only)
#endif

  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  CAN0.setCANPins((gpio_num_t)RX_PIN, (gpio_num_t)TX_PIN);
  CAN0.begin(CAN_BPS_500K);
  CAN0.watchFor(CAN_REPLY_ID);
  CAN0.setCallback(0, callback);
}

void loop() {
  requestCar();
  if( rpm > 2000 ) { digitalWrite(YELLOW_LED, HIGH); }
  else             { digitalWrite(YELLOW_LED, LOW);  }
  Serial.println(rpm);
  delay(200);
}



void requestCar(void) {  
  CAN_FRAME outgoing;
  outgoing.id = CAN_REQST_ID;
  outgoing.length = 8;
  outgoing.extended = 0;
  outgoing.rtr = 0;
  outgoing.data.uint8[0] = 0x02;  
  outgoing.data.uint8[1] = 0x01;  
  outgoing.data.uint8[2] = CANPID_RPM; 
  outgoing.data.uint8[3] = 0x00;
  outgoing.data.uint8[4] = 0x00;  
  outgoing.data.uint8[5] = 0x00;  
  outgoing.data.uint8[6] = 0x00;  
  outgoing.data.uint8[7] = 0x00;  
  CAN0.sendFrame(outgoing);
}


void callback(CAN_FRAME *from_car) {
  digitalWrite(BLUE_LED, HIGH);
  delay(20);
  digitalWrite(BLUE_LED, LOW);
  if (from_car->data.uint8[2]==CANPID_RPM) {
    uint8_t rpmOBDH = from_car->data.uint8[3];
    uint8_t rpmOBDL = from_car->data.uint8[4];
    rpm = (uint16_t) ((256*rpmOBDH) + rpmOBDL)/(float)4;
  }
}
