#ifndef SENSOR_H
#define SENSOR_H
#include "../utils.h"

class Sensor {
    uint _pin;

  public:
    Sensor(uint pin);
    // ~Sensor();
    // virtual void update();
    void print();
};

#endif // SENSOR_H