#include "bot.h"
#include "../../include/utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

ERUSBot::ERUSBot(EngineT::PinData left, EngineT::PinData right,
                 const uint sensorPins[SENSOR_COUNT]) {
    printf("creating bot...\n");
    this->engineLeft = std::unique_ptr<Engine>(new Engine(left, "LEFT"));

    this->engineRight = std::unique_ptr<Engine>(new Engine(right, "RIGHT"));
    printf("motors created successfully...\n");

    // for (int i = 0; i < SENSOR_COUNT; i++) {
    //     printf("iter %d, target pin = %d\n", i, sensorPins[i]);
    //     this->sensors[i] = std::unique_ptr<Sensor>(new
    //     Sensor(sensorPins[i]));
    // }
    printf("Bot init successfully!\n");
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