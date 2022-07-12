#include <Arduino.h>

#include "bot.h"
#include "pins.h"
#include "secret.h"
#include <iostream>
#include <memory.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot(
    {Pins::Engine::left::power, Pins::Engine::left::direction::forward,
     Pins::Engine::left::direction::backward},
    {Pins::Engine::right::power, Pins::Engine::right::direction::forward,
     Pins::Engine::right::direction::backward},
    Pins::sensors));

void setup() {
    std::cout << Colors::blue << "[INFO] " << Colors::reset
              << "Connecting to SSID \"" << WIFI_SSID << "\" with password \""
              << WIFI_PASSWORD << "\"" << std::endl;
}

void loop() {

    // bot.debug();
    // bot.tick();
    delay(10);
}
