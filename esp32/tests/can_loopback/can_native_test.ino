#include "driver/twai.h"

#define CAN_TX GPIO_NUM_21
#define CAN_RX GPIO_NUM_22

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=== ESP32 Native CAN (TWAI) Init Test ===");

  // General CAN configuration
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(
      CAN_TX,
      CAN_RX,
      TWAI_MODE_NO_ACK
  );

  // 500 kbps CAN speed (OBD-II standard)
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();

  // Accept all CAN IDs for now
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  // Install CAN driver
  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
    Serial.println("TWAI driver installed");
  } else {
    Serial.println("TWAI driver install FAILED");
    while (1);
  }

  // Start CAN driver
  if (twai_start() == ESP_OK) {
    Serial.println("TWAI driver started");
  } else {
    Serial.println("TWAI driver start FAILED");
    while (1);
  }

  Serial.println("CAN controller is ready (no bus connected)");
}

void loop() {
  twai_message_t tx_msg = {};
  tx_msg.identifier = 0x123;          // arbitrary test ID
  tx_msg.extd = 0;                    // standard ID
  tx_msg.rtr = 0;                     // data frame
  tx_msg.data_length_code = 8;

  for (int i = 0; i < 8; i++) {
    tx_msg.data[i] = i;
  }

  esp_err_t result = twai_transmit(&tx_msg, pdMS_TO_TICKS(1000));

  if (result == ESP_OK) {
    Serial.println("TX OK (no ACK expected)");
  } else {
    Serial.println("TX FAILED");
  }

  delay(1000);
}
