#include "engine.h"
#include <Arduino.h>

Engine::Engine(EngineT::PinData pins, std::string id) {
    this->pins = pins;
    this->id = id;

    pinMode(pins.powerPin, OUTPUT);
    pinMode(pins.directionPinForward, OUTPUT);
    pinMode(pins.directionPinBackward, OUTPUT);

    digitalWrite(pins.directionPinForward, LOW);
    digitalWrite(pins.directionPinBackward, LOW);
    digitalWrite(pins.powerPin, LOW);

    this->currentValue = 0;
}

Engine::Engine(EngineT::PinData pins) { Engine(pins, "UNINDENTIFIED"); }

void Engine::tick() {}

std::string Engine::toString() {
    return "{\n\tID: " + std::string(this->id) + "\n\t" +
           "VALUE: " + std::to_string(this->currentValue) + "\n}";
}