#ifndef SENSOR_ARRAY_H
#define SENSOR_ARRAY_H

#include <memory>

#include "../../include/sharedTypes.h"
#include "sensor.h"
#include "timer.h"

#define SENSOR_COUNT 5
#define SENSOR_MIN_THRESHOLD 0.1
#define SENSOR_MAX_THRESHOLD 0.5
#define SENSOR_MIDWAY_POINT 0.5

#define MIN_DETECT_TIME 0.1

class SensorArray {
    std::unique_ptr<Sensor> sensors[SENSOR_COUNT];
    float minThreshold;
    float maxThreshold;
    bool isFarRight, isFarLeft;

    std::unique_ptr<Timer> leftSensorTimer, rightSensorTimer, centerSensorTimer;

    uint leftMarks, rightMarks;
    bool canIncreaseLeftMarks, canIncreaseRightMarks;

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
    bool sensorsAreFarLeft() { return this->isFarRight; };
    bool sensorsAreFarRight() { return this->isFarLeft; };
    uint getLeftMarks() { return this->leftMarks; }
    uint getRightMarks() { return this->rightMarks; }
};

#endif