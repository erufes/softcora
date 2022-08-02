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
    float getReading() { return this->reading; }
    // ~Sensor();
    // virtual void update();
    std::string toString();
};

#endif // SENSOR_H