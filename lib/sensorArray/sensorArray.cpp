#include "sensorArray.h"
#include "../../include/pins.h"

SensorArray::SensorArray() {
    this->minThreshold = SENSOR_MIN_THRESHOLD;
    this->maxThreshold = SENSOR_MAX_THRESHOLD;
    for (int i = 0; i < SENSOR_COUNT; i++) {
        printf("iter %d, target pin = %d\n", i, Pins::sensors[i]);
        this->sensors[i] =
            std::unique_ptr<Sensor>(new Sensor(Pins::sensors[i]));
    }
    this->isFarRight = false;
    this->isFarLeft = false;
}

bool SensorArray::isReadingLeftMark() {
    return this->sensors[Sensor::LEFT]->getReading() > this->minThreshold;
}

bool SensorArray::isReadingRightMark() {
    return this->sensors[Sensor::RIGHT]->getReading() > this->minThreshold;
}

void SensorArray::tick() {
    for (auto& sensor : this->sensors) {
        sensor.get()->tick();
    }
}

float SensorArray::estimateLinePosition5(bool whiteLine) {
    float avg = 0;
    float div = 0;
    for (int i = 0; i < SENSOR_COUNT; i++) {
        float val = this->sensors[i].get()->getReading();
        if (whiteLine) {
            val = 1 - val;
        }
        if (val > this->minThreshold) {
            avg += (i + 1) * val;
            div += val;
        }
    }
    if (div == 0) {
        // printf('"\n[SensorArray] %s Error: attempted to divide by 0!%s\n",
        //        Co'lors::red, Colors::reset);
        return 0;
    }
    return (avg / div);
}

float SensorArray::estimateLinePosition2(bool whiteLine) {
    float valR = 0, valL = 0;

    valL = this->sensors[1].get()->getReading();
    if (whiteLine) {
        valL = 1 - valL;
    }
    valR = this->sensors[3].get()->getReading();
    if (whiteLine) {
        valR = 1 - valR;
    }

    // This should always be between 0 and 1
    float result = (valR - valL) * 0.5f + .5f;

    if (result >
        SENSOR_MIDWAY_POINT + this->maxThreshold * SENSOR_MIDWAY_POINT) {
        isFarLeft = true;
    }
    if (result <
        SENSOR_MIDWAY_POINT - (this->maxThreshold * SENSOR_MIDWAY_POINT)) {
        isFarRight = true;
    }

    if (isFarLeft && result < SENSOR_MIDWAY_POINT - this->minThreshold) {
        isFarLeft = false;
    }
    if (isFarRight && result > SENSOR_MIDWAY_POINT + this->minThreshold) {
        isFarRight = false;
    }

    return result;

    // return avg / div;
}

void SensorArray::updatePIDValues(PIDControl& oldPIDValues) {
    uint position = this->estimateLinePosition2() * 4000;
    // This works for 2 sensors specifically!
    static const uint midway = 2000;

    int proportional = position - midway;
    int derivative = proportional - oldPIDValues.proportional;

    oldPIDValues.integral += proportional;
    oldPIDValues.proportional = proportional;
    oldPIDValues.derivative = derivative;

    oldPIDValues.powerDiff = oldPIDValues.derivative * oldPIDValues.kd +
                             oldPIDValues.integral * oldPIDValues.ki +
                             oldPIDValues.proportional * oldPIDValues.kp;
}

void SensorArray::getReadings(uint values[5]) {
    for (int i = 0; i < SENSOR_COUNT; i++) {
        values[i] = this->sensors[i].get()->getReading();
    }
}

std::string SensorArray::toString() {
    char str[999];
    sprintf(str, "SensorArray: ");
    for (int i = 0; i < SENSOR_COUNT; i++) {
        sprintf(str, "%s\n%s", str, this->sensors[i].get()->toString().c_str());
    }
    sprintf(str, "%s\n\n", str);
    return std::string(str);
}