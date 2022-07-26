#include "bot.h"
#include "../../include/utils.h"
#include <cstdlib>
#include <iostream>

using namespace std;

ERUSBot::ERUSBot(EngineT::PinData m1, EngineT::PinData m2,
                 const uint sensorPins[SENSOR_COUNT]) {
    printf("creating bot...\n");
    this->motor1 = std::unique_ptr<Engine>(new Engine(m1, "MOTOR1"));

    this->motor2 = std::unique_ptr<Engine>(new Engine(m2, "MOTOR2"));
    printf("motors created successfully...\n");

    // for (int i = 0; i < SENSOR_COUNT; i++) {
    //     printf("iter %d, target pin = %d\n", i, sensorPins[i]);
    //     this->sensors[i] = std::unique_ptr<Sensor>(new
    //     Sensor(sensorPins[i]));
    // }
    printf("Bot init successfully!\n");
}

void ERUSBot::tick() {
    this->motor1->tick();
    this->motor2->tick();
    for (auto& sensor : this->sensors) {
        sensor.get()->tick();
    }
}

void ERUSBot::debug() {
    printf("%c[2J%c[H", 27, 27); // clear screen command
    cout << "Engine Stats" << endl
         << Colors::green << this->motor1->toString() << endl
         << this->motor2->toString() << Colors::reset << endl;
}

Engine* ERUSBot::getMotor1() { return this->motor1.get(); }