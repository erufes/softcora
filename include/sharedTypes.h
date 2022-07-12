#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
#include "utils.h"

namespace EngineT {
    typedef struct pinData {
        uint powerPin;
        uint directionPinForward;
        uint directionPinBackward;
    } PinData;

    enum class Direction { FORWARD, BACKWARD };
    enum class Side { LEFT, RIGHT };
}

#endif