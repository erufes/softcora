#include <Arduino.h>

#include "bot.h"
#include "pins.h"
#include "secret.h"
#include <memory.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot(
    {Pins::Engine::left::power, Pins::Engine::left::direction::forward,
     Pins::Engine::left::direction::backward},
    {Pins::Engine::right::power, Pins::Engine::right::direction::forward,
     Pins::Engine::right::direction::backward},
    Pins::sensors));

void setup() {
    printf("Setup called...\n");
    printf("Connecting to ssid \"%s\" with password \"%s\"...\n", WIFI_SSID,
           WIFI_PASSWORD);
}

void loop() {

    // bot.debug();
    // bot.tick();
    delay(10);
}
