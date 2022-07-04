#include "bot.h"

ERUSBot::ERUSBot() {
    this->engineLeft = std::unique_ptr<Engine>();
    this->engineRight = std::unique_ptr<Engine>();
}

void ERUSBot::tick() {
    printf("ERUSBot::tick()\n");
    this->engineLeft->tick();
    this->engineRight->tick();
}