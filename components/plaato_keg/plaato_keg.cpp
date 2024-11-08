#include "plaato_keg.h"
#include "Adafruit_PCT2075.h"

namespace esphome {
namespace plaato_keg {

static const char *TAG = "plaato_keg.sensor";

void PlaatoKeg::setup() {
}

void PlaatoKeg::loop() {
  
}

void PlaatoKeg::update() {
  if (this->temp_sensor_ != nullptr) {
    TwoWire I2CPCT = TwoWire(0);
    Adafruit_PCT2075 PCT2075;
    float temp = PCT2075.getTemperature();
    ESP_LOGD("main", "temperature: %0.2f°C", temp);
    this->temp_sensor_->publish_state(temp);
  }
}

void PlaatoKeg::dump_config() {
  ESP_LOGCONFIG(TAG, "Plaato Keg sensor");
}

} //namespace plaato_keg
} //namespace esphome
