#ifndef ENGINE_H
#define ENGINE_H

#define ID_MAX_LENGTH 17

#include "../../include/sharedTypes.h"
#include "../../include/utils.h"
#include <string>

class Engine {
    std::string id;
    EngineT::PinData pins;
    uint currentValue;

  public:
    Engine(EngineT::PinData pins, std::string id);
    Engine(EngineT::PinData pins);
    // ~Engine();
    void tick();
    std::string toString();

    // void print();
};

#endif // ENGINE_H