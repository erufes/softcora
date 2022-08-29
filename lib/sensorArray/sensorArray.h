#ifndef SENSOR_ARRAY_H
#define SENSOR_ARRAY_H

#include <memory>

#include "../../include/sharedTypes.h"
#include "sensor.h"

#define SENSOR_COUNT 5
#define SENSOR_MIN_THRESHOLD 0.1

class SensorArray {
    std::unique_ptr<Sensor> sensors[SENSOR_COUNT];

  public:
    SensorArray();
    void tick();
    void calibrate();
    void read();
    void getReadings(uint values[5]);
    std::string toString();
    bool isReadingLeftMark();
    bool isReadingRightMark();
    uint estimateLinePosition(bool whiteLine = false);
    void updatePIDParams(float kp, float ki, float kd);
    void updatePIDValues(PIDControl& oldPIDValues);
};

#endif