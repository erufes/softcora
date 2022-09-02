#include "sensor.h"
#include <Arduino.h>
#include <stdio.h>

Sensor::Sensor(pinType pin) {
    this->pin = pin;
    this->reading = 0;
    pinMode(this->pin, INPUT);
    printf("Sensor @ pin %d created successfully!\n", pin);
}

std::string Sensor::toString() {
    char str[99];
    sprintf(str, "Sensor %d - %.2f", this->pin, this->reading);
    return std::string(str);
}

void Sensor::tick() { this->read(); }

void Sensor::calibrate() {}

void Sensor::read() { this->reading = float(analogRead(this->pin)) / 4096; }
