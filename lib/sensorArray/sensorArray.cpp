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
    this->leftSensorTimer =
        std::unique_ptr<Timer>(new Timer(MIN_DETECT_TIME * SECONDS));
    this->rightSensorTimer =
        std::unique_ptr<Timer>(new Timer(MIN_DETECT_TIME * SECONDS));
    this->centerSensorTimer =
        std::unique_ptr<Timer>(new Timer(MIN_DETECT_TIME * SECONDS));

    this->leftMarks = 0;
    this->rightMarks = 0;
    this->canIncreaseLeftMarks = true;
    this->canIncreaseRightMarks = true;
}

bool SensorArray::isReadingLeftMark() {
    return this->sensors[Sensor::LEFT]->getReading() > this->maxThreshold;
}

bool SensorArray::isReadingRightMark() {
    return this->sensors[Sensor::RIGHT]->getReading() > this->maxThreshold;
}

void SensorArray::tick() {
    for (auto& sensor : this->sensors) {
        sensor.get()->tick();
    }

    Timer* leftSensorTimer = this->leftSensorTimer.get();
    Timer* rightSensorTimer = this->rightSensorTimer.get();

    // if (leftSensorTimer->isDone()) {
    //     if (this->canIncreaseLeftMarks) {
    //         this->leftMarks++;
    //         this->canIncreaseLeftMarks = false;
    //     }
    //     leftSensorTimer->reset();
    //     leftSensorTimer->stop();
    // }

    // {
    //     if (leftSensorTimer->isDone()) {
    //         if (this->canIncreaseLeftMarks) {
    //             this->leftMarks++;
    //             this->canIncreaseLeftMarks = false;
    //         }
    //         leftSensorTimer->reset();
    //         leftSensorTimer->stop();
    //     }

    //     if (rightSensorTimer->isDone()) {
    //         this->rightMarks++;
    //         rightSensorTimer->reset();
    //         rightSensorTimer->stop();
    //         this->canIncreaseRightMarks = false;
    //     }
    // }
    if (!this->isReadingLeftMark()) {
        this->canIncreaseLeftMarks = true;
    }
    if (!this->isReadingRightMark()) {
        this->canIncreaseRightMarks = true;
    }

    if (leftSensorTimer->isDone()) {
        if (this->canIncreaseLeftMarks)
            this->leftMarks++;
        this->canIncreaseLeftMarks = false;
        leftSensorTimer->reset();
        leftSensorTimer->stop();
    }
    if (rightSensorTimer->isDone()) {
        if (this->canIncreaseRightMarks)
            this->rightMarks++;
        this->canIncreaseRightMarks = false;
        rightSensorTimer->reset();
        rightSensorTimer->stop();
    }

    {
        if (!isReadingLeftMark()) {
            leftSensorTimer->stop();
            leftSensorTimer->reset();
        } else {
            if (leftSensorTimer->getIsRunning()) {
                leftSensorTimer->tick();
            } else {
                leftSensorTimer->start();
            }
        }

        if (!isReadingRightMark()) {
            rightSensorTimer->stop();
            rightSensorTimer->reset();
        } else {
            if (rightSensorTimer->getIsRunning()) {
                rightSensorTimer->tick();
            } else {
                rightSensorTimer->start();
            }
        }
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