#include "driver/twai.h"


#define USB_SPEED     500000 // 115200 230400 250000 500000

#define RX_PIN        13
#define TX_PIN        14
#define CAN_RS        38



void setup() {
  Serial.begin(USB_SPEED);
  Serial.setTxTimeoutMs(0);   // prevent slow timeouts
  pinMode(CAN_RS, OUTPUT);    // INPUT (high impedance) = slope control mode, OUTPUT = see next line
  digitalWrite(CAN_RS, LOW);  // LOW = high speed mode, HIGH = low power mode (listen only)
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_LISTEN_ONLY);  // TWAI_MODE_NORMAL, TWAI_MODE_NO_ACK or TWAI_MODE_LISTEN_ONLY
  twai_timing_config_t t_config  = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config  = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  twai_driver_install(&g_config, &t_config, &f_config);
  twai_start();
}


void loop() {
  twai_message_t message;
  
  if (twai_receive(&message, 0) == ESP_OK) {
    Serial.print("0x");
    Serial.print(message.identifier, HEX);
    Serial.print("\t");
    Serial.print(message.extd);
    Serial.print("\t");
    Serial.print(message.rtr);
    Serial.print("\t");
    Serial.print(message.data_length_code);
    
    for(int i=0;i<message.data_length_code;i++) {
      Serial.print("\t0x");
      if (message.data[i]<=0x0F) {
        Serial.print(0);
      }
      Serial.print(message.data[i], HEX);
    }
    Serial.println();
  }
}
