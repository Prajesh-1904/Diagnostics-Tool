#include <Arduino.h>
#include "driver/twai.h"

// ===== CAN PINS (ESP32 DevKit V1) =====
#define CAN_TX GPIO_NUM_21
#define CAN_RX GPIO_NUM_22

// ===== CAN INIT =====
void can_init() {
  twai_general_config_t g_config =
      TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX, CAN_RX, TWAI_MODE_NORMAL);

  twai_timing_config_t t_config =
      TWAI_TIMING_CONFIG_500KBITS();

  twai_filter_config_t f_config =
      TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
    Serial.println("CAN driver install failed");
    while (1);
  }

  if (twai_start() != ESP_OK) {
    Serial.println("CAN driver start failed");
    while (1);
  }

  Serial.println("CAN started");
}

// ======================================================
// ===================== MOCK ECU =======================
// ======================================================
#ifdef ROLE_MOCK_ECU

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Mock ECU booting...");
  can_init();
}

void loop() {
  twai_message_t req;

  if (twai_receive(&req, pdMS_TO_TICKS(1000)) == ESP_OK) {

    // OBD-II RPM request: 02 01 0C
    if (req.identifier == 0x7DF &&
        req.data[1] == 0x01 &&
        req.data[2] == 0x0C) {

      Serial.println("RPM request received");

      // Fake RPM = 3000
      // (3000 * 4) = 12000 = 0x2EE0
      twai_message_t resp = {};
      resp.identifier = 0x7E8;
      resp.data_length_code = 8;

      resp.data[0] = 0x04;
      resp.data[1] = 0x41;
      resp.data[2] = 0x0C;
      resp.data[3] = 0x2E;
      resp.data[4] = 0xE0;

      twai_transmit(&resp, pdMS_TO_TICKS(1000));
    }
  }
}

#endif

// ======================================================
// ===================== TESTER =========================
// ======================================================
#ifdef ROLE_TESTER

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("OBD Tester booting...");
  can_init();
}

void loop() {

  // Send RPM request
  twai_message_t req = {};
  req.identifier = 0x7DF;
  req.data_length_code = 8;

  req.data[0] = 0x02;
  req.data[1] = 0x01;
  req.data[2] = 0x0C;

  twai_transmit(&req, pdMS_TO_TICKS(1000));
  Serial.println("RPM request sent");

  // Wait for response
  twai_message_t resp;
  if (twai_receive(&resp, pdMS_TO_TICKS(1000)) == ESP_OK) {

    if (resp.identifier == 0x7E8 &&
        resp.data[1] == 0x41 &&
        resp.data[2] == 0x0C) {

      uint16_t raw =
        (resp.data[3] << 8) | resp.data[4];

      uint16_t rpm = raw / 4;

      Serial.print("RPM = ");
      Serial.println(rpm);
    }
  }

  delay(2000);
}

#endif
