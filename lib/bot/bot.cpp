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

    this->sensors = std::unique_ptr<SensorArray>(new SensorArray());

    this->led1 = std::unique_ptr<Led>(new Led(Pins::LEDs::led1));
    this->led2 = std::unique_ptr<Led>(new Led(Pins::LEDs::led2));

    this->pidData = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    this->leftMarks = 0;
    this->rightMarks = 0;

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
    cout << "Sensor Readings" << endl
         << Colors::green << this->sensors.get()->toString() << Colors::reset
         << endl;
}

void ERUSBot::checkSideMarks() {
    if (this->sensors.get()->isReadingLeftMark()) {
        this->leftMarks++;
    }
    if (this->sensors.get()->isReadingRightMark()) {
        this->rightMarks++;
    }
}

void ERUSBot::tickSensors() {
    this->sensors.get()->tick();
    // this->checkSideMarks();
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

void ERUSBot::updatePIDParams(float kp, float ki, float kd) {
    this->pidData.kp = kp;
    this->pidData.ki = ki;
    this->pidData.kd = kd;
}

// TODO: Needs further testing!
void ERUSBot::updateMotorState() {
    // Compute the difference between the two motor power settings,
    // m1 - m2.  If this is a positive number the robot will turn
    // to the right.  If it is a negative number, the robot will
    // turn to the left, and the magnitude of the number determines
    // the sharpness of the turn.
    // pietroluongo: this refers to this->pidData.powerDiff

    uint power_difference = this->pidData.powerDiff;

    // Compute the actual motor settings.  We never set either motor
    // to a negative value.
    const int max = 60;
    if (power_difference > max)
        power_difference = max;
    if (power_difference < -max)
        power_difference = -max;

    if (power_difference < 0) {
        this->motor1->setSpeed(max + power_difference);
        this->motor2->setSpeed(max);
    } else {
        this->motor1->setSpeed(max);
        this->motor2->setSpeed(max - power_difference);
    }
}
