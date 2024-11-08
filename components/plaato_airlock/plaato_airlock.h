#pragma once

#include "esphome.h"
#include "sensor/sensor.h"

namespace esphome {
namespace plaato_airlock {

class PlaatoAirlock : public PollingComponent {
 public:
  // Constructor with polling interval
  PlaatoAirlock() : PollingComponent(10000) {}

  // Setup method for initial setup
  void setup() override;

  // Update method, called at each polling interval
  void update() override;

  // Setters for linking to ESPHome sensors configured in YAML
  void set_temperature_sensor(sensor::Sensor *temp_sensor) { temperature_sensor_ = temp_sensor; }
  void set_bubble_count_sensor(sensor::Sensor *bubble_count_sensor) { bubble_count_sensor_ = bubble_count_sensor; }

 protected:
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *bubble_count_sensor_{nullptr};

  // Logic to calculate temperature and bubble count
  float calculate_temperature();
  float calculate_bubble_count();
};

}  // namespace plaato_airlock
}  // namespace esphome
