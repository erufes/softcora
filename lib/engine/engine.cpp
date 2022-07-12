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
    this->direction = EngineT::Direction::FORWARD;
}

Engine::Engine(EngineT::PinData pins) { Engine(pins, "UNINDENTIFIED"); }

void Engine::tick() {
    if (this->direction == EngineT::Direction::FORWARD) {
        digitalWrite(this->pins.directionPinForward, HIGH);
        digitalWrite(this->pins.directionPinBackward, LOW);
    } else {
        digitalWrite(this->pins.directionPinForward, LOW);
        digitalWrite(this->pins.directionPinBackward, HIGH);
    }

    analogWrite(this->pins.powerPin, this->currentValue);
}

std::string Engine::toString() {
    return "{\n\tID: " + std::string(this->id) + "\n\t" +
           "VALUE: " + std::to_string(this->currentValue) + "\n}";
}