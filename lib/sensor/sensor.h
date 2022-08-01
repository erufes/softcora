#ifndef SENSOR_H
#define SENSOR_H
#include "../../include/utils.h"
#include <Arduino.h>
#include <string>

#define QTR_EMITTERS_OFF 0
#define QTR_EMITTERS_ON 1
#define QTR_EMITTERS_ON_AND_OFF 2

static constexpr int64_t TIMEOUT = 1024;

class Sensor {
    byte pin;
    float reading;

    void emitterOn();
    void emitterOff();

    unsigned char emitterBitmask;
    unsigned char* emitterPORT;
    unsigned char* emitterDDR;

  public:
    Sensor(uint pin);
    void tick();
    void calibrate();
    void read(unsigned char readMode = QTR_EMITTERS_ON);
    // ~Sensor();
    // virtual void update();
    std::string toString();
};

#endif // SENSOR_H