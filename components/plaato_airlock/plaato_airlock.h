#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace plaato_airlock {

class PlaatoAirlock : public sensor::Sensor, public PollingComponent {
  public:  
    void set_temp_sensor(sensor::Sensor *temp_sensor) { temp_sensor_ = temp_sensor; }
    void set_bubble_sensor(sensor::Sensor *bubble_sensor) { bubble_sensor_ = bubble_sensor; }

    void setup() override;
    void loop() override;
    void update() override;
    void dump_config() override;

  protected:
    sensor::Sensor *temp_sensor_;
    sensor::Sensor *bubble_sensor_;
};

} //namespace plaato_airlock
} //namespace esphome
