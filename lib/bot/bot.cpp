#include "bot.h"
#include "../../include/pins.h"
#include "../../include/utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

ERUSBot::ERUSBot() {

    printf("creating bot...\n");
    this->motor1 = std::unique_ptr<Engine>(
        new Engine({Pins::Engine::M1::Power, Pins::Engine::M1::Direction::DirA,
                    Pins::Engine::M1::Direction::DirB},
                   "MOTOR1"));

    this->motor2 = std::unique_ptr<Engine>(
        new Engine({Pins::Engine::M2::Power, Pins::Engine::M2::Direction::DirA,
                    Pins::Engine::M2::Direction::DirB},
                   "MOTOR2"));

    printf("motors created successfully...\n");

    this->motorEnablePin = Pins::Engine::enable;
    this->motorFaultPin = Pins::Engine::fault;

    this->batteryPin = Pins::battery;

    for (int i = 0; i < SENSOR_COUNT; i++) {
        printf("iter %d, target pin = %d\n", i, Pins::sensors[i]);
        this->sensors[i] =
            std::unique_ptr<Sensor>(new Sensor(Pins::sensors[i]));
    }
    this->led1 = std::unique_ptr<Led>(new Led(Pins::LEDs::led1));
    this->led2 = std::unique_ptr<Led>(new Led(Pins::LEDs::led2));

    printf("Bot init successfully!\n");
}

void ERUSBot::tick() {
    // this->tickSensors();
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

void ERUSBot::updateState() {
    switch (this->currentState) {
    // TODO
    default:
        break;
    }
}

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