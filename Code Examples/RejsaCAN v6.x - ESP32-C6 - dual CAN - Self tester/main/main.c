#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h"
#include "led_strip.h"



#define CAN0_RX       23
#define CAN0_TX       3
#define CAN1_RX       20
#define CAN1_TX       21
#define RGB_LED       8

#define CANPID_RPM    0x0C
#define CAN_REQST_ID  0x7DF 
#define CAN_REPLY_ID  0x7E8

#define EXAMPLE_TAG   "TWAI v2"


static twai_handle_t twai_bus_0;
static twai_handle_t twai_bus_1;
static led_strip_handle_t rgb_led;
static uint16_t rpm;  


static void send_request (void) {
  twai_message_t tx_message;
  tx_message.identifier = CAN_REQST_ID;
  tx_message.extd = 0;
  tx_message.rtr = 0;
  tx_message.data_length_code = 8;
  tx_message.data[0] = 0x02;
  tx_message.data[1] = 0x01;
  tx_message.data[2] = CANPID_RPM;
  tx_message.data[3] = 0xAA;
  tx_message.data[4] = 0xAA;
  tx_message.data[5] = 0xAA;
  tx_message.data[6] = 0xAA;
  tx_message.data[7] = 0xAA; 
  ESP_LOGI(EXAMPLE_TAG, "Sending request for 0x%02X ... ", tx_message.data[2]);
  twai_transmit_v2(twai_bus_0, &tx_message, 0); 
  ESP_LOGI(EXAMPLE_TAG, "done");
  led_strip_set_pixel(rgb_led, 0, 100, 0, 0);
  led_strip_refresh(rgb_led);
}

static void receive_reply (void) {
  twai_message_t rx_message;
  if (twai_receive_v2( twai_bus_0, &rx_message, 0) == ESP_OK  &&  rx_message.identifier == CAN_REPLY_ID ) {
    ESP_LOGI(EXAMPLE_TAG, "Received reply for 0x%02X with data 0x%02X 0x%02X", rx_message.data[2], rx_message.data[3], rx_message.data[4]);
    if (rx_message.data[2]==CANPID_RPM) {
      uint8_t rpmOBDH = rx_message.data[3];
      uint8_t rpmOBDL = rx_message.data[4];
      rpm = (uint16_t) ((256*rpmOBDH) + rpmOBDL)/(float)4;
      ESP_LOGI(EXAMPLE_TAG, "rpm %d", rpm);
      led_strip_set_pixel(rgb_led, 0, 0, 0, rpm/256);
      led_strip_refresh(rgb_led);
    }
  }
}

void obd2_reply (void) {
	
  twai_message_t rx_message;
  twai_message_t tx_message;
  static unsigned char dummy = 0;

  if (twai_receive_v2(twai_bus_1, &rx_message, 0) == ESP_OK) {
    ESP_LOGI(EXAMPLE_TAG, "OBD2 replying to request for 0x%02X with data %hhu", rx_message.data[2], dummy);
    tx_message.identifier = CAN_REPLY_ID;
    tx_message.extd = 0;
    tx_message.rtr = 0;
    tx_message.data_length_code = 8;
    tx_message.data[0] = 0x03;
    tx_message.data[1] = 0x41;
    tx_message.data[2] = rx_message.data[2];
    tx_message.data[3] = dummy;
    tx_message.data[4] = 0xAA;
    tx_message.data[5] = 0xAA;
    tx_message.data[6] = 0xAA;
    tx_message.data[7] = 0xAA; 
    twai_transmit_v2(twai_bus_1, &tx_message, 0); 
    dummy++;
    led_strip_set_pixel(rgb_led, 0, 0, 100, 0);
    led_strip_refresh(rgb_led);
  }
}



void app_main(void)
{
  ESP_LOGI(EXAMPLE_TAG, "Booting...");

  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN0_TX, CAN0_RX, TWAI_MODE_NORMAL);  // TWAI_MODE_NORMAL, TWAI_MODE_NO_ACK or TWAI_MODE_LISTEN_ONLY
  twai_timing_config_t t_config  = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config  = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  g_config.controller_id = 0;
  ESP_ERROR_CHECK(twai_driver_install_v2(&g_config, &t_config, &f_config, &twai_bus_0));
  ESP_LOGI(EXAMPLE_TAG, "Driver 0 installed");
  ESP_ERROR_CHECK(twai_start_v2(twai_bus_0));
  ESP_LOGI(EXAMPLE_TAG, "Driver 0 started");

  g_config.controller_id = 1;
  g_config.tx_io = CAN1_TX;
  g_config.rx_io = CAN1_RX;
  ESP_ERROR_CHECK(twai_driver_install_v2(&g_config, &t_config, &f_config, &twai_bus_1));
  ESP_LOGI(EXAMPLE_TAG, "Driver 1 installed");
  ESP_ERROR_CHECK(twai_start_v2(twai_bus_1));
  ESP_LOGI(EXAMPLE_TAG, "Driver 1 started");

  led_strip_config_t strip_config = { .strip_gpio_num = RGB_LED, .max_leds = 1, };
  led_strip_rmt_config_t rmt_config = {};
  led_strip_new_rmt_device(&strip_config, &rmt_config, &rgb_led);
  led_strip_clear(rgb_led);

  while (true) {
    send_request();
    vTaskDelay(pdMS_TO_TICKS(50));   
    obd2_reply();
    vTaskDelay(pdMS_TO_TICKS(50));   
    receive_reply();
    vTaskDelay(pdMS_TO_TICKS(500));   
  }
}