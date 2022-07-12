#include <Arduino.h>

#include "bot.h"
#include "env.h"
#include "pins.h"
#include <memory.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot(
    {Pins::Engine::left::power, Pins::Engine::left::direction::forward,
     Pins::Engine::left::direction::backward},
    {Pins::Engine::right::power, Pins::Engine::right::direction::forward,
     Pins::Engine::right::direction::backward},
    Pins::sensors));

void setup() { printf("Setup called...\n"); }

void loop() {
    printf("all ok! - var is %s\n", WIFI_PASSWORD);
    // bot.debug();
    // bot.tick();
    delay(10);
}
