#include "led.h"

Led::Led(byte pin) {
    // TODO
}

void Led::on() {
    digitalWrite(0, HIGH);
    this->state = true;
}
void Led::off() {
    digitalWrite(0, LOW);
    this->state = false;
}

bool Led::isOn() { return this->state; }

bool Led::isOff() { return !this->state; }
void Led::tick() { // TODO
}
void Led::blink(int64_t interval, int64_t duration) {}

void Led::stopBlink() {}
