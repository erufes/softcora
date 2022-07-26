#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
#include "utils.h"
#include <Arduino.h>

namespace EngineT {
    typedef struct pinData {
        byte powerPin;
        byte directionPinA;
        byte directionPinB;
    } PinData;

    typedef struct sharedPinData {
        byte faultPin;
        byte enablePin;
    } SharedPinData;

    typedef struct packedPinData {
        pinData m1;
        pinData m2;
        sharedPinData s;
    } PackedPinData;

    enum class Direction { FORWARD, BACKWARD, BRAKE, COAST };
    enum class Side { LEFT, RIGHT };

}

#endif