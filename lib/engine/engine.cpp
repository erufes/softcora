#include "engine.h"
#include <Arduino.h>

Engine::Engine(EngineT::PinData pins, std::string id) {
    this->pins = pins;
    this->id = id;

    pinMode(pins.powerPin, OUTPUT);
    pinMode(pins.directionPinA, OUTPUT);
    pinMode(pins.directionPinB, OUTPUT);

    digitalWrite(pins.directionPinA, LOW);
    digitalWrite(pins.directionPinB, LOW);
    digitalWrite(pins.powerPin, LOW);

    this->currentValue = 0;
    this->direction = EngineT::Direction::FORWARD;
}

Engine::Engine(EngineT::PinData pins) { Engine(pins, "UNINDENTIFIED"); }

void Engine::tick() {
    if (this->direction == EngineT::Direction::FORWARD) {
        digitalWrite(this->pins.directionPinA, HIGH);
        digitalWrite(this->pins.directionPinB, LOW);
    } else {
        digitalWrite(this->pins.directionPinA, LOW);
        digitalWrite(this->pins.directionPinB, HIGH);
    }

    analogWrite(this->pins.powerPin, this->currentValue);
}

std::string Engine::toString() {
    return "{\n\tID: " + std::string(this->id) + "\n\t" +
           "VALUE: " + std::to_string(this->currentValue) + "\n}";
}

void Engine::setSpeed(int speed) {}