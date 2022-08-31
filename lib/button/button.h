#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

class Button {
    byte pin;

    public:
        Button(byte pin);
        bool isPressed();
};

#endif