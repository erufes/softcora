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

    enum class Direction { FORWARD, BACKWARD };
    enum class Side { LEFT, RIGHT };
}

#endif