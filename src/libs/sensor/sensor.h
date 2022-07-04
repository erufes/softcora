#ifndef SENSOR_H
#define SENSOR_H
#include "../utils.h"
#include <string>

class Sensor {
    uint _pin;

  public:
    Sensor(uint pin);
    void tick();
    // ~Sensor();
    // virtual void update();
    std::string toString();
};

#endif // SENSOR_H