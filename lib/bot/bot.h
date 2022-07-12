#ifndef BOT_H
#define BOT_H

#include "../../include/sharedTypes.h"
#include "engine.h"
#include "sensor.h"
#include <memory>

class ERUSBot {
    std::unique_ptr<Engine> engineLeft;
    std::unique_ptr<Engine> engineRight;

    std::unique_ptr<Sensor> sensors[5];

  public:
    ERUSBot(EngineT::PinData left, EngineT::PinData right,
            const uint sensorPins[5]);
    void tick();
    void debug();
};

#endif // BOT_H