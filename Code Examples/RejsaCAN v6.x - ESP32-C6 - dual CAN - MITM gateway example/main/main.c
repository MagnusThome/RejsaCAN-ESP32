#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h"



#define CAN0_RX       23
#define CAN0_TX       3
#define CAN1_RX       20
#define CAN1_TX       21
#define EXAMPLE_TAG   "TWAI v2"

static twai_handle_t twai_bus_0;
static twai_handle_t twai_bus_1;


void forward (void) {
  twai_message_t message;
  if (twai_receive_v2(twai_bus_0, &message, 0) == ESP_OK) {
    twai_transmit_v2(twai_bus_1, &message, 0); 
    ESP_LOGI(EXAMPLE_TAG, "x0%" PRIX32 "\n", message.identifier);
  }
}

void reverse (void) {
  twai_message_t message;
  if (twai_receive_v2(twai_bus_1, &message, 0) == ESP_OK) {
    twai_transmit_v2(twai_bus_0, &message, 0); 
    ESP_LOGI(EXAMPLE_TAG, "x0%" PRIX32 "\n", message.identifier);
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

  while (true) {
    forward();
    reverse();
  }
}