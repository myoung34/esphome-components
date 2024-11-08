#include "plaato_airlock.h"

namespace esphome {
namespace plaato_airlock {

void PlaatoAirlock::setup() {
  // Log setup completion for debugging
  ESP_LOGI("plaato_airlock", "Plaato Airlock setup complete");
}

void PlaatoAirlock::update() {
  // Calculate and publish temperature if temperature_sensor_ is set
  if (temperature_sensor_ != nullptr) {
    float temp = calculate_temperature();
    ESP_LOGD("plaato_airlock", "Temperature: %.2f", temp);
    temperature_sensor_->publish_state(temp);
  }

  // Calculate and publish bubble count if bubble_count_sensor_ is set
  if (bubble_count_sensor_ != nullptr) {
    float bubble_count = calculate_bubble_count();
    ESP_LOGD("plaato_airlock", "Bubble Count: %.2f", bubble_count);
    bubble_count_sensor_->publish_state(bubble_count);
  }
}

float PlaatoAirlock::calculate_temperature() {
  // Wake up, read temperature, and shut down sensor
  temperature_sensor_.wake_up();
  temperature_sensor_.read_temperature();
  temperature_sensor_.shut_down();

  // Retrieve and return temperature value
  float temp = temperature_sensor_.get_temperature();
  return temp;
}

float PlaatoAirlock::calculate_bubble_count() {
  // Synchronize with STM8, set LED state, and retrieve bubble count
  stm8.sync();
  stm8.set_led(SLOWBREATHING);
  int bubble_count = stm8.get_count();
  return static_cast<float>(bubble_count);
}

}  // namespace plaato_airlock
}  // namespace esphome
