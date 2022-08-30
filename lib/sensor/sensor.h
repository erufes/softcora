#ifndef SENSOR_H
#define SENSOR_H
#include "../../include/sharedTypes.h"
#include "../../include/utils.h"
#include <Arduino.h>
#include <string>

class Sensor {
    pinType pin;
    float reading;

  public:
    Sensor(pinType pin);
    void tick();
    void calibrate();
    void read();
    // Between 0 and 1
    float getReading() { return this->reading; }
    // ~Sensor();
    // virtual void update();
    std::string toString();

    static constexpr pinType LEFT = 0;
    static constexpr pinType LEFT_FRONT = 1;
    static constexpr pinType CENTER = 2;
    static constexpr pinType RIGHT_FRONT = 3;
    static constexpr pinType RIGHT = 4;
};

#endif // SENSOR_H