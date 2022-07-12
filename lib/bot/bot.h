#ifndef BOT_H
#define BOT_H

#define SENSOR_COUNT 5

#include "../../include/sharedTypes.h"
#include "engine.h"
#include "sensor.h"
#include <memory>

class ERUSBot {
    std::unique_ptr<Engine> engineLeft;
    std::unique_ptr<Engine> engineRight;

    std::unique_ptr<Sensor> sensors[SENSOR_COUNT];

  public:
    ERUSBot(EngineT::PinData left, EngineT::PinData right,
            const uint sensorPins[SENSOR_COUNT]);
    void tick();
    void debug();
};

#endif // BOT_H