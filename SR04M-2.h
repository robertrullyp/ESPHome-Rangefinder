#include "esphome.h"

class UltrasonicSensor : public PollingComponent, public UARTDevice, public Sensor {
  public:
    UltrasonicSensor(UARTComponent *parent) : PollingComponent(1000), UARTDevice(parent) {}

    void setup() override {

    }

    int calculate_sum(uint8_t h_data, uint8_t l_data) {
      int sum_result = (h_data + l_data) & 0x00FF;
      return sum_result;
    }

    void update() override {
      uint8_t buffer[3];

      if (available() >= 4) {
        read_array(buffer, 3);

        uint8_t start_byte = buffer[0];
        uint8_t h_data = buffer[1];
        uint8_t l_data = buffer[2];
        uint8_t sum_data = buffer[3];

        if (start_byte == 0xFF) {
          int distance = (h_data << 8) | l_data;
          float cmdistance = distance / 10.0;
          int sum_result = calculate_sum(h_data, l_data);

          ESP_LOGD("Ultrasonic", "Jarak [cm]: %.1f | 0x%04X | SUM: 0x%02X", cmdistance, distance, sum_result);

          if (sum_result == sum_data) {
            publish_state(cmdistance);
          } else {
            ESP_LOGW("Ultrasonic", "Checksum tidak sesuai, data tidak valid!");
          }
        } else {
          ESP_LOGW("Ultrasonic", "Start byte tidak valid!");
        }
      }
    }
};
// return {new UltrasonicSensor(id(my_uart))};