#ifndef LED_H
#define LED_H
#include <Arduino.h>

class Led {
    byte pin;
    bool state;
    int64_t blinkInterval;
    int64_t blinkDuration;
    int64_t lastBlink;

  public:
    Led(byte pin);
    void on();
    void off();
    bool isOn();
    bool isOff();
    void tick();
    void blink(int64_t interval, int64_t duration);
    void stopBlink();
};

#endif