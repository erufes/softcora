#include "sensor.h"
#include <Arduino.h>
#include <stdio.h>

Sensor::Sensor(uint pin) {
    this->pin = pin;
    printf("Sensor @ pin %d created successfully!\n", pin);
}

std::string Sensor::toString() { return "all ok!"; }

void Sensor::tick() {
    this->read();
    printf("[Sens %d] reading: %.2f\%\n", this->pin, this->reading);
}

void Sensor::calibrate() {}

void Sensor::read() { this->reading = float(analogRead(this->pin)) / 4096; }
