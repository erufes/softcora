#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
#include "utils.h"
#include <Arduino.h>

typedef byte pinType;

namespace EngineT {
    typedef struct pinData {
        pinType powerPin;
        pinType directionPinA;
        pinType directionPinB;
    } PinData;

    typedef struct sharedPinData {
        pinType faultPin;
        pinType enablePin;
    } SharedPinData;

    typedef struct packedPinData {
        pinData m1;
        pinData m2;
        sharedPinData s;
    } PackedPinData;

    enum class Direction { FORWARD, BACKWARD, BRAKE, COAST };
    enum class Side { LEFT, RIGHT };

}

typedef struct PIDControl {
    float kp;
    float ki;
    float kd;
    int integral;
    int derivative;
    int proportional;
    int powerDiff;
} PIDControl;

#endif