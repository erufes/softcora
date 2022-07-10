#include "engine.h"
#include <Arduino.h>

Engine::Engine(uint pin, std::string id) {
    this->pin = pin;
    this->id = id;
    pinMode(pin, OUTPUT);
    this->currentValue = 0;
}

Engine::Engine(uint pin) { Engine(pin, "UNINDENTIFIED"); }

void Engine::tick() {}

std::string Engine::toString() {
    return "{\n\tID: " + std::string(this->id) + "\n\t" +
           "PIN: " + std::to_string(this->pin) + "\n\t" +
           "VALUE: " + std::to_string(this->currentValue) + "\n}";
}