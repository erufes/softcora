#include "sensor.h"
#include <Arduino.h>
#include <stdio.h>

Sensor::Sensor(uint pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
}

void Sensor::print() { printf("all ok!\n"); }