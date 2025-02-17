#include "esphome.h"

class UltrasonicSensor : public PollingComponent, public UARTDevice, public Sensor {
  public:
    UltrasonicSensor(UARTComponent *parent) : PollingComponent(10000), UARTDevice(parent) {}

    void setup() override {

    }

    void update() override {

      write_byte(0xA0); // Kirim perintah untuk mulai membaca
      set_timeout(150, [this]() {
      // delay(150);
        uint8_t Data_h = 0, Data_m = 0, Data_l = 0;
        float distance = 0;

        if (available() >= 3) {
          Data_h = read();
          Data_m = read();
          Data_l = read();
        } else {
          Data_h = 0;
          Data_m = 0;
          Data_l = 0;
        }
        distance = (Data_h * 65536 + Data_m * 256 + Data_l) / 10000.0;

        if (distance >= 1 && distance <= 900) {
          publish_state(distance);
          // ESP_LOGD("Ultrasonic", "Distance: %.2f cm", distance);
        } else {
          ESP_LOGD("Ultrasonic", "Invalid Data: %d, %d, %d", Data_h, Data_m, Data_l);
        }
      });
    }
};
// return {new UltrasonicSensor(id(my_uart))};