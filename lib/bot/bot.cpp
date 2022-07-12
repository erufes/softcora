#include "bot.h"
#include "../../include/utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

ERUSBot::ERUSBot(EngineT::PinData left, EngineT::PinData right,
                 const uint sensorPins[5]) {
    this->engineLeft = std::unique_ptr<Engine>(new Engine(left, "LEFT"));

    this->engineRight = std::unique_ptr<Engine>(new Engine(right, "RIGHT"));

    for (int i = 0; i < 5; i++) {
        this->sensors[i] = std::unique_ptr<Sensor>(new Sensor(sensorPins[i]));
    }
}

void ERUSBot::tick() {
    this->engineLeft->tick();
    this->engineRight->tick();
    for (auto& sensor : this->sensors) {
        sensor.get()->tick();
    }
}

void ERUSBot::debug() {
    printf("%c[2J%c[H", 27, 27); // clear screen command
    cout << "Engine Stats" << endl
         << Colors::green << this->engineLeft->toString() << endl
         << this->engineRight->toString() << Colors::reset << endl;
}