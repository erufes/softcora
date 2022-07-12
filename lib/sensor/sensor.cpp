#include "sensor.h"
#include <Arduino.h>
#include <stdio.h>

Sensor::Sensor(uint pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
    printf("Sensor @ pin %d created successfully!\n", _pin);
}

std::string Sensor::toString() { return "all ok!"; }

void Sensor::tick() {}

void Sensor::calibrate() {}