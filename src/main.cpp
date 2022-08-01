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

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot(
    {{Pins::Engine::M1::Power, Pins::Engine::M1::Direction::DirA,
      Pins::Engine::M1::Direction::DirB},
     {Pins::Engine::M2::Power, Pins::Engine::M2::Direction::DirA,
      Pins::Engine::M2::Direction::DirB},
     EngineT::SharedPinData{Pins::Engine::fault, Pins::Engine::enable}},
    Pins::sensors, Pins::battery));

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
static int64_t timeout = 1024;

int dirFlags = 0;

void nextFlag() { dirFlags = (dirFlags + 1) % 4; }

// static Sensor s = Sensor(32);

void loop() {
    // pinMode(32, OUTPUT);
    // digitalWrite(32, HIGH);
    // delayMicroseconds(15);
    // int64_t now = esp_timer_get_time();
    // pinMode(32, INPUT);
    // while (1) {
    //     if (digitalRead(32) == LOW || esp_timer_get_time() - now > timeout)
    //         break;
    // }

    // int64_t diff = esp_timer_get_time() - now;
    // float percent = float(diff) / 1024;
    // printf("diff: %.2f\%\n", percent);

    // s.read();

    // Engine* mot1 = bot->getMotor1();
    // Engine* mot2 = bot->getMotor2();
    // currentTime = esp_timer_get_time();
    // int64_t delta = currentTime - lastTime;
    // // if (delta > 2000000) {
    // if (delta > 200000) {
    //     lastTime = currentTime;
    //     nextFlag();
    //     printf("battery reads %.2f\n", bot->getBatteryVoltage());
    //     printf("raw battery reads %d\n", bot->getRawBatteryVoltage());

    //     switch (dirFlags) {
    //     case 0:
    //         // printf("setting speed to 0\n");
    //         mot1->setSpeed(0);
    //         mot2->setSpeed(0);
    //         break;
    //     case 1:
    //         // printf("setting speed to 255\n");
    //         mot1->setSpeed(255);
    //         mot2->setSpeed(255);
    //         break;
    //     case 2:
    //         // printf("setting speed to -255\n");
    //         mot1->setSpeed(-255);
    //         mot2->setSpeed(-255);
    //         break;
    //     case 3:
    //         // printf("setting speed to 100\n");
    //         mot1->setSpeed(100);
    //         mot2->setSpeed(100);
    //         break;
    //     }
    // }

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
