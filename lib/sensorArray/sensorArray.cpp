#include "sensorArray.h"
#include "../../include/pins.h"

SensorArray::SensorArray() {
    for (int i = 0; i < SENSOR_COUNT; i++) {
        printf("iter %d, target pin = %d\n", i, Pins::sensors[i]);
        this->sensors[i] =
            std::unique_ptr<Sensor>(new Sensor(Pins::sensors[i]));
    }
}

bool SensorArray::isReadingLeftMark() {
    return this->sensors[Sensor::LEFT]->getReading() > SENSOR_MIN_THRESHOLD;
}

bool SensorArray::isReadingRightMark() {
    return this->sensors[Sensor::RIGHT]->getReading() > SENSOR_MIN_THRESHOLD;
}

void SensorArray::tick() {
    for (auto& sensor : this->sensors) {
        sensor.get()->tick();
    }
}

// TODO: test!
uint SensorArray::estimateLinePosition(bool whiteLine) {
    uint avg = 0;
    uint div = 0;
    for (int i = 0; i < SENSOR_COUNT; i++) {
        uint val = this->sensors[i].get()->getReading();
        if (whiteLine) {
            val = 1 - val;
        }
        if (val > SENSOR_MIN_THRESHOLD) {
            avg += i * val;
            div += val;
        }
    }
    return avg / div;
}

void SensorArray::updatePIDValues(PIDControl& oldPIDValues) {
    uint position = this->estimateLinePosition();
    static const uint midway = SENSOR_COUNT / 2;
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