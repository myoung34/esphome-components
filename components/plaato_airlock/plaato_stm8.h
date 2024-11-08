#pragma once

#include <Wire.h>

class  Plaato_stm8 {
  private:
    int address = 0x3;
    uint32_t bubble_count = 0;
    uint32_t bubble_size_total = 0;
    bool reset_flag = false;
  public:
    bool setup() {
      Wire.begin(14,12);
      uint8_t i = 0;
      while(digitalRead(14) == 0 ) { // if SDA is low, do (max) 10 cycles on SCL.
		    delayMicroseconds(4);
		    GPES = (1 << 12); // SCL low
		    delayMicroseconds(4);
		    GPEC = (1 << 12); // SCL high
		    i++;
		    if (i >= 10) {
		    	return false;
		    }
		  }
		  return true;
    }

    bool set_led(uint8_t led_mode) {
      Wire.beginTransmission(address);
      Wire.write(led_mode);
      if (Wire.endTransmission() == 0) {
        return true;
      } else {
        return false;
      }
    }

    bool sync() {
			uint8_t bytes[5];
			Wire.beginTransmission(address);
			if (Wire.requestFrom(address, 5) == 5) {
				bytes[0] = Wire.read();
				bytes[1] = Wire.read();
				bytes[2] = Wire.read();
				bytes[3] = Wire.read();
				bytes[4] = Wire.read();
				if (Wire.endTransmission() == 0) {
					if (bytes[0]) {
					  reset_flag = true;
					} else {
					  reset_flag = false;
					}

					bubble_count = (uint32_t)bytes[4] | (uint32_t)bytes[3] << 8| (uint32_t)bytes[2] << 16 | (uint32_t)bytes[1] << 24;
          return true;
				} else {
					return false;
				}
			}
			return false;
    }

    bool sync2() {
      uint8_t bytes[9];
      Wire.beginTransmission(address);
      if (Wire.requestFrom(address, 9) == 9) {
        bytes[0] = Wire.read();
        bytes[1] = Wire.read();
        bytes[2] = Wire.read();
        bytes[3] = Wire.read();
        bytes[4] = Wire.read();
        bytes[5] = Wire.read();
        bytes[6] = Wire.read();
        bytes[7] = Wire.read();
        bytes[8] = Wire.read();
        if (Wire.endTransmission() == 0) {
          if (bytes[0]) {
            reset_flag = true;
          } else {
            reset_flag = false;
          }

          bubble_count = (uint32_t)bytes[4] | (uint32_t)bytes[3] << 8| (uint32_t)bytes[2] << 16 | (uint32_t)bytes[1] << 24;
          bubble_size_total = (uint32_t)bytes[8] | (uint32_t)bytes[7] << 8| (uint32_t)bytes[6] << 16 | (uint32_t)bytes[5] << 24;
          return true;
        } else {
          return false;
        }
      }
      return false;
    }

    uint32_t get_count() {
      return bubble_count;
    }

    uint32_t get_size() {
      return bubble_size_total;
    }

    bool get_reset_flag() {
      return reset_flag;
    }
};

