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

    byte motorEnablePin;
    byte motorFaultPin;

    byte batteryPin;

    void tickSensors();
    void tickMotors();
    void updateState();
    void updateLED();
    void checkButtons();
    bool checkMotorFault();

  public:
    ERUSBot(EngineT::PackedPinData enginePinData,
            const uint sensorPins[SENSOR_COUNT], const uint batteryPin);
    void tick();
    void debug();
    Engine* getMotor1() { return this->motor1.get(); }
    Engine* getMotor2() { return this->motor2.get(); }
    void enableMotors() { digitalWrite(this->motorEnablePin, HIGH); }
    void disableMotors() { digitalWrite(this->motorEnablePin, LOW); }
    float getBatteryVoltage();
    uint getRawBatteryVoltage();
};

#endif // BOT_H