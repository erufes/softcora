#include "engine.h"
#include <Arduino.h>

Engine::Engine(uint pin, char *id) {
  this->pin = pin;
  strncpy(this->id, id, ID_MAX_LENGTH);
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