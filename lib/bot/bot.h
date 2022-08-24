#ifndef BOT_H
#define BOT_H

#define SENSOR_COUNT 1
#define SENSOR_MIN_THRESHOLD 0.1

#include "../../include/sharedTypes.h"
#include "engine.h"
#include "led.h"
#include "sensor.h"
#include <memory>

typedef struct PIDControl {
    float kp;
    float ki;
    float kd;
    float integral;
    float derivative;
    float lastError;
} PIDControl;

// Note: Use this class as a singleton!
class ERUSBot {
    std::unique_ptr<Engine> motor1;
    std::unique_ptr<Engine> motor2;

    std::unique_ptr<Sensor> sensors[SENSOR_COUNT];

    std::unique_ptr<Led> led1;
    std::unique_ptr<Led> led2;

    byte motorEnablePin;
    byte motorFaultPin;

    byte batteryPin;

    void tickSensors();
    void tickMotors();
    void updateState();
    void updateLED();
    void checkButtons();
    bool checkMotorFault();

    enum BotState { IDLE, MOVING, STOPPED, ERROR };

    BotState currentState;

    PIDControl pidData;

  public:
    ERUSBot();
    void tick();
    void debug();
    Engine* getMotor1() { return this->motor1.get(); }
    Engine* getMotor2() { return this->motor2.get(); }
    void enableMotors() { digitalWrite(this->motorEnablePin, HIGH); }
    void disableMotors() { digitalWrite(this->motorEnablePin, LOW); }
    float getBatteryVoltage();
    uint getRawBatteryVoltage();
    uint estimateLinePosition(bool whiteLine = false);
};

#endif // BOT_H