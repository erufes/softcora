#include "bot.h"
#include "../../include/utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

ERUSBot::ERUSBot(EngineT::PackedPinData enginePinData,
                 const uint sensorPins[SENSOR_COUNT], const uint batteryPin) {
    printf("creating bot...\n");
    this->motor1 =
        std::unique_ptr<Engine>(new Engine(enginePinData.m1, "MOTOR1"));

    this->motor2 =
        std::unique_ptr<Engine>(new Engine(enginePinData.m2, "MOTOR2"));
    printf("motors created successfully...\n");

    this->motorEnablePin = enginePinData.s.enablePin;
    this->motorFaultPin = enginePinData.s.faultPin;

    this->batteryPin = batteryPin;

    for (int i = 0; i < SENSOR_COUNT; i++) {
        printf("iter %d, target pin = %d\n", i, sensorPins[i]);
        this->sensors[i] = std::unique_ptr<Sensor>(new Sensor(sensorPins[i]));
    }
    printf("Bot init successfully!\n");
}

void ERUSBot::tick() {
    this->tickSensors();
    this->checkButtons();
    this->updateState();
    this->updateLED();

    this->tickMotors();
}

void ERUSBot::debug() {
    printf("%c[2J%c[H", 27, 27); // clear screen command
    cout << "Engine Stats" << endl
         << Colors::green << this->motor1->toString() << endl
         << this->motor2->toString() << Colors::reset << endl;
}

void ERUSBot::tickSensors() {
    for (auto& sensor : this->sensors) {
        sensor.get()->tick();
    }
}

void ERUSBot::tickMotors() {
    this->motor1->tick();
    this->motor2->tick();
}

void ERUSBot::updateState() {}

void ERUSBot::updateLED() {}

void ERUSBot::checkButtons() {}

bool ERUSBot::checkMotorFault() {
    if (digitalRead(this->motorFaultPin) == HIGH) {
        printf("h-bridge fault detected!\n");
        return true;
    }
    return false;
}

float ERUSBot::getBatteryVoltage() {
    return 0;
    // TODO
    uint originalValue = analogRead(this->batteryPin);
    return (((float)originalValue / 4096 * 3.3) - 2.46) / 0.05;
    // float result = 1024 * originalValue / 3.5;
    // return result * 3.325;
}
uint ERUSBot::getRawBatteryVoltage() { return analogRead(this->batteryPin); }