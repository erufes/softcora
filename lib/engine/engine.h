#ifndef ENGINE_H
#define ENGINE_H

#define ID_MAX_LENGTH 17

#include "../../include/sharedTypes.h"
#include "../../include/utils.h"
#include <string>

class Engine {
    std::string id;
    EngineT::PinData pins;
    byte currentValue;
    EngineT::Direction direction;
    EngineT::Side side;

  public:
    Engine(EngineT::PinData pins, std::string id);
    Engine(EngineT::PinData pins);
    void tick();
    std::string toString();

    void setDirection(EngineT::Direction direction) {
        this->direction = direction;
    }

    // sets the motor speed.  The sign of 'speed' determines the direction
    // and the magnitude determines the speed.  limits: -255 <= speed < 255
    // |speed| = 255 produces the maximum speed while speed = 0 is full brake.
    void setCommit(int value);

    EngineT::Direction getDirection() { return this->direction; }
    uint getValue() { return this->currentValue; }
    EngineT::Side getSide() { return this->side; }
};

#endif // ENGINE_H