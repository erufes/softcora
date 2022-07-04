#include "bot.h"
#include <iostream>

ERUSBot::ERUSBot() {
    this->engineLeft = std::unique_ptr<Engine>(new Engine(3, "LEFT"));
    this->engineRight = std::unique_ptr<Engine>(new Engine(5, "RIGHT"));
}

void ERUSBot::tick() {
    printf("ERUSBot::tick()\n");
    this->engineLeft->tick();
    this->engineRight->tick();
    std::cout << this->engineLeft->toString() << std::endl
              << this->engineRight->toString() << std::endl;
}