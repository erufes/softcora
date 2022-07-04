#ifndef ENGINE_H
#define ENGINE_H

#include "../utils.h"

class Engine {
    uint _pin;
    uint _currentValue;

  public:
    Engine();
    // ~Engine();
    void tick();
    // void print();
};

#endif // ENGINE_H