#ifndef ENGINE_H
#define ENGINE_H

#define ID_MAX_LENGTH 17

#include "../../include/sharedTypes.h"
#include "../../include/utils.h"
#include <string>

class Engine {
    std::string id;
    EngineT::PinData pins;

    uint currentSpeed;
    EngineT::Direction direction;
    EngineT::Side side;

    void updateDirectionPins();

  public:
    Engine(EngineT::PinData pins, std::string id);
    Engine(EngineT::PinData pins);

    void tick();

    // sets the motor speed.  The sign of 'speed' determines the direction
    // and the magnitude determines the speed.  limits: -255 <= speed < 255
    // |speed| = 255 produces the maximum speed while speed = 0 is full brake.
    void setSpeed(int speed);

    void coast();
    void brake();
    void forward();
    void backward();

    EngineT::Direction getDirection() { return this->direction; }
    uint getSpeed() { return this->currentSpeed; }
    EngineT::Side getSide() { return this->side; }

    std::string toString();
};

#endif // ENGINE_H