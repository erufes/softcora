#include <Arduino.h>

#include "AsyncUDP.h"
#include "WiFi.h"

#include "bot.h"
#include "net.h"
#include "pins.h"
#include "secrets.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <iostream>
#include <memory.h>
#include <time.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(
    new ERUSBot({Pins::Engine::M1::Power, Pins::Engine::M1::Direction::DirA,
                 Pins::Engine::M1::Direction::DirB},
                {Pins::Engine::M2::Power, Pins::Engine::M2::Direction::DirA,
                 Pins::Engine::M2::Direction::DirB},
                Pins::sensors));

Connection* c;
int64_t lastTime;

void setup() {

    lastTime = esp_timer_get_time();
    // std::cout << Colors::blue << "[INFO] " << Colors::reset
    //           << "Connecting to SSID \"" << WIFI_SSID << "\" with password\""
    //           << WIFI_PASSWORD << "\"" << std::endl;
    // WiFi.mode(WIFI_STA);
    // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(3000);
    //     std::cout << Colors::red << "[ERROR] " << Colors::reset
    //               << "Failed to connect to SSID \"" << WIFI_SSID
    //               << "\" with password \"" << WIFI_PASSWORD << "\".
    //               Retrying..."
    //               << std::endl;
    // }
    // std::cout << Colors::green << "[SUCCESS] " << Colors::reset
    //           << "Connected to WiFi" << std::endl;

    // c = new Connection("192.168.0.125", 20002);
}

static int64_t currentTime;

int dirFlags = 0;

void loop() {
    Engine* e = bot->getMotor1();
    currentTime = esp_timer_get_time();
    int64_t delta = currentTime - lastTime;
    if (delta > 1000000) {
        lastTime = currentTime;
        if (e->getDirection() == EngineT::Direction::BACKWARD) {
            e->setDirection(EngineT::Direction::FORWARD);
        } else {
            e->setDirection(EngineT::Direction::BACKWARD);
        }
    }

    // printf("broadcasting hello world\n");
    // bot.debug();
    bot->tick();
    // printf("loop()\n");
    // digitalWrite(Pins::Engine::M1::Direction::DirA, HIGH);
    // digitalWrite(Pins::Engine::M1::Direction::DirB, LOW);
    // printf("A\n");
    // delay(1000);
    // digitalWrite(Pins::Engine::M1::Direction::DirA, LOW);
    // digitalWrite(Pins::Engine::M1::Direction::DirB, HIGH);
    // printf("B\n");
    // delay(1000);
}
