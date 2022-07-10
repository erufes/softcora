#ifndef ENGINE_H
#define ENGINE_H

#define ID_MAX_LENGTH 17

#include "../../include/utils.h"
#include <string>

class Engine {
    std::string id;
    uint pin;
    uint currentValue;

  public:
    Engine(uint pin, std::string id);
    Engine(uint pin);
    // ~Engine();
    void tick();
    std::string toString();

    // void print();
};

#endif // ENGINE_H