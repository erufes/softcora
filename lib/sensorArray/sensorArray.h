#ifndef SENSOR_ARRAY_H
#define SENSOR_ARRAY_H

#include <memory>

#include "../../include/sharedTypes.h"
#include "sensor.h"

#define SENSOR_COUNT 5
#define SENSOR_MIN_THRESHOLD 0.1

class SensorArray {
    std::unique_ptr<Sensor> sensors[SENSOR_COUNT];
    float minThreshold;

  public:
    SensorArray();
    void tick();
    void calibrate();
    void read();
    void getReadings(uint values[5]);
    std::string toString();
    bool isReadingLeftMark();
    bool isReadingRightMark();
    float estimateLinePosition5(bool whiteLine = false);
    float estimateLinePosition2(bool whiteLine = false);
    void updatePIDParams(float kp, float ki, float kd);
    void updatePIDValues(PIDControl& oldPIDValues);
    void setThreshold(float threshold) { this->minThreshold = threshold; }
};

#endif