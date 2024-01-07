/*

* * * Works with ESP32-S3 * * *

Good for an initial test in the car to check that the board and the car's OBD connector work as they should

- Blue LED blinks when *ANY* CAN replies are received from the car
- Yellow LED is on when the engine rpm is over 2000 rpm
- Engine rpms are continously printed over the serial on USB-port and over BLE 

*/

#include <Arduino.h>
#include "driver/twai.h"
#include "ble_uart.h"

#define BLUE_LED      10
#define YELLOW_LED    11

#define RX_PIN        13
#define TX_PIN        14
#define CAN_RS        38

#define CANPID_RPM    0x0C
#define CAN_REQST_ID  0x7DF 
#define CAN_REPLY_ID  0x7E8

uint16_t rpm;



void setup() {
  Serial.begin(115200);
  Serial.setTxTimeoutMs(0); // prevent slow serial prints if no usb
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(CAN_RS, OUTPUT);    // INPUT (high impedance) = slope control mode, OUTPUT = see next line
  digitalWrite(CAN_RS, LOW);  // LOW = high speed mode, HIGH = low power mode (listen only)
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NORMAL);  // TWAI_MODE_NORMAL, TWAI_MODE_NO_ACK or TWAI_MODE_LISTEN_ONLY
  twai_timing_config_t t_config  = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config  = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  twai_driver_install(&g_config, &t_config, &f_config);
  twai_start();
  ble_setup();
}


void loop() {
  unsigned long loopnow = millis();

  ble_loop();

  #define TIMERONE 100
  static unsigned long timerone = TIMERONE;
  if (loopnow - timerone >= TIMERONE) {
    timerone = loopnow;
    can_sendrequest(CANPID_RPM);
  }  
  
  can_recvreply();

  #define TIMERTWO 250
  static unsigned long timertwo = TIMERTWO;
  if (loopnow - timertwo >= TIMERTWO) {
    timertwo = loopnow;
	  ble_send(rpm);
  }

}



void can_sendrequest (uint8_t obd2) {
  twai_message_t message;
  message.identifier = CAN_REQST_ID;
  message.extd = 0;
  message.rtr = 0;
  message.data_length_code = 8;
  message.data[0] = 2;
  message.data[1] = 1;
  message.data[2] = obd2;
  message.data[3] = 0xAA;
  message.data[4] = 0xAA;
  message.data[5] = 0xAA;
  message.data[6] = 0xAA;
  message.data[7] = 0xAA; 
  twai_transmit(&message, pdMS_TO_TICKS(1000)); 
}



void can_recvreply (void) {
  twai_message_t message;
  if (twai_receive(&message, pdMS_TO_TICKS(1)) != ESP_OK) {
    return;
  }
  digitalWrite(BLUE_LED, HIGH);
  delay(5);
  digitalWrite(BLUE_LED, LOW);

  if (message.data[2]==CANPID_RPM) {
    uint8_t rpmOBDH = message.data[3];
    uint8_t rpmOBDL = message.data[4];
    rpm = (uint16_t) ((256*rpmOBDH) + rpmOBDL)/(float)4;
    if( rpm > 2000 ) { digitalWrite(YELLOW_LED, HIGH); }
    else             { digitalWrite(YELLOW_LED, LOW);  }
    Serial.print("can_recvreply rpm: ");
    Serial.println(rpm);
  }
}
