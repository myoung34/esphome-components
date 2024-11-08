#include "plaato_airlock_sensor.h"

#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"

namespace esphome {
namespace plaato_airlock {

static const char *TAG = "plaato_airlock.sensor";

float PlaatoAirlockSensor::get_setup_priority() const { return setup_priority::DATA; }

void PlaatoAirlockSensor::setup() { ESP_LOGCONFIG(TAG, "Setting up PlaatoAirlockSensor..."); }

void PlaatoAirlockSensor::update() {
  uint32_t bubble_count = 0;
  uint32_t bubble_total = 0;

  if (this->bubble_count_sensor_ != nullptr) {
    this->bubble_count_sensor_->publish_state(bubble_count);
  }
  if (this->bubble_total_sensor_ != nullptr) {
    this->bubble_total_sensor_->publish_state(bubble_total);
  }
  /* FIXME: implement checking for reset flag
      if (bytes[0]) {
        reset_flag = true;
      } else {
        reset_flag = false;
      }
  */
}

void PlaatoAirlockSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "PlaatoAirlock Sensor:");
  LOG_SENSOR("  ", "BubbleCountSensor", this->bubble_count_sensor_);
  LOG_SENSOR("  ", "BubbleTotalSensor", this->bubble_total_sensor_);
}

}  // namespace plaato_airlock
}  // namespace esphome
