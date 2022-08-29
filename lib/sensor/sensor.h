#ifndef SENSOR_H
#define SENSOR_H
#include "../../include/utils.h"
#include <Arduino.h>
#include <string>

class Sensor {
    byte pin;
    float reading;

  public:
    Sensor(uint pin);
    void tick();
    void calibrate();
    void read();
    // Between 0 and 1
    float getReading() { return this->reading; }
    // ~Sensor();
    // virtual void update();
    std::string toString();

    static constexpr uint LEFT = 0;
    static constexpr uint LEFT_FRONT = 1;
    static constexpr uint CENTER = 2;
    static constexpr uint RIGHT_FRONT = 3;
    static constexpr uint RIGHT = 4;
};

#endif // SENSOR_H