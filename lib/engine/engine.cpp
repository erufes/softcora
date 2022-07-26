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

    this->currentSpeed = 0;
    this->direction = EngineT::Direction::FORWARD;
}

Engine::Engine(EngineT::PinData pins) { Engine(pins, "UNINDENTIFIED"); }

void Engine::tick() { analogWrite(this->pins.powerPin, this->currentSpeed); }

std::string Engine::toString() {
    return "{\n\tID: " + std::string(this->id) + "\n\t" +
           "VALUE: " + std::to_string(this->currentSpeed) + "\n}";
}

void Engine::updateDirectionPins() {
    switch (direction) {
    case EngineT::Direction::FORWARD:
        digitalWrite(pins.directionPinA, HIGH);
        digitalWrite(pins.directionPinB, LOW);
        break;
    case EngineT::Direction::BACKWARD:
        digitalWrite(pins.directionPinA, LOW);
        digitalWrite(pins.directionPinB, HIGH);
        break;
    case EngineT::Direction::BRAKE:
        digitalWrite(pins.directionPinA, HIGH);
        digitalWrite(pins.directionPinB, HIGH);
        break;
    case EngineT::Direction::COAST:
        digitalWrite(pins.directionPinA, LOW);
        digitalWrite(pins.directionPinB, LOW);
        break;
    }
}

void handleSpeedOverflow(int& speed) {
    if (speed > 255) {
        printf("[Motor] [Warning] Exceeded max speed.\n");
        speed = 255;
    } else if (speed < -255) {
        printf("[Motor] [Warning] Exceeded min speed.\n");
        speed = -255;
    }
}

void setDirectionFromSpeed(int& speed, EngineT::Direction& direction) {
    if (speed > 0) {
        direction = EngineT::Direction::FORWARD;
    } else if (speed < 0) {
        direction = EngineT::Direction::BACKWARD;
    } else {
        direction = EngineT::Direction::BRAKE;
    }
}

void Engine::setSpeed(int speed) {
    handleSpeedOverflow(speed);

    this->currentSpeed = speed;

    setDirectionFromSpeed(speed, this->direction);

    updateDirectionPins();
}

void Engine::coast() {
    this->direction = EngineT::Direction::COAST;
    this->updateDirectionPins();
}
void Engine::brake() {
    this->direction = EngineT::Direction::BRAKE;
    this->updateDirectionPins();
}