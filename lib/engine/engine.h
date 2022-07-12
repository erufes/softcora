#ifndef ENGINE_H
#define ENGINE_H

#define ID_MAX_LENGTH 17

#include "../../include/utils.h"
#include <string>

typedef struct pinData {
    uint powerPin;
    uint directionPinForward;
    uint directionPinBackward;
} PinData;

class Engine {
    std::string id;
    PinData pins;
    uint currentValue;

  public:
    Engine(PinData pins, std::string id);
    Engine(PinData pins);
    // ~Engine();
    void tick();
    std::string toString();

    // void print();
};

#endif // ENGINE_H