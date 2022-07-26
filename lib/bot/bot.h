#ifndef BOT_H
#define BOT_H

#define SENSOR_COUNT 5

#include "../../include/sharedTypes.h"
#include "engine.h"
#include "sensor.h"
#include <memory>

class ERUSBot {
    std::unique_ptr<Engine> motor1;
    std::unique_ptr<Engine> motor2;

    std::unique_ptr<Sensor> sensors[SENSOR_COUNT];

  public:
    ERUSBot(EngineT::PinData m1, EngineT::PinData m2,
            const uint sensorPins[SENSOR_COUNT]);
    void tick();
    void debug();
    Engine* getMotor1();
    Engine* getMotor2();
};

#endif // BOT_H