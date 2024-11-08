#include "plaato_airlock.h"
#include "plaato_stm8.h"
#include "pct2075.h"

namespace esphome {
namespace plaato_airlock {

static const char *TAG = "plaato_airlock.sensor";

void PlaatoAirlock::setup() {
}

void PlaatoAirlock::loop() {
  
}

void PlaatoAirlock::update() {
  if (this->temp_sensor_ != nullptr) {
    Pct2075 temperature_sensor;
    temperature_sensor.wake_up();
    temperature_sensor.read_temperature();
    temperature_sensor.shut_down();
    float temp = temperature_sensor.get_temperature();
    ESP_LOGD("main", "temperature: %0.2f°C", temp);
    this->temp_sensor_->publish_state(temp);
  }
  if (this->bubble_sensor_ != nullptr) {
    Plaato_stm8 stm8;
    // Check for reset and get bubblecount
    stm8.sync();

    // Set LED on STM8
    stm8.set_led(3);

    // Get values and publish them
    int bubble_count = stm8.get_count();

    ESP_LOGD("main", "bubbles: %d", bubble_count);
    this->bubble_sensor_->publish_state(bubble_count);
  }
}

void PlaatoAirlock::dump_config() {
  ESP_LOGCONFIG(TAG, "Plaato Airlock sensor");
}

} //namespace plaato_airlock
} //namespace esphome
