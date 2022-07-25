#include <Arduino.h>

#include "AsyncUDP.h"
#include "WiFi.h"

#include "bot.h"
#include "net.h"
#include "pins.h"
#include "secrets.h"
#include <iostream>
#include <memory.h>

static std::unique_ptr<ERUSBot> bot = std::unique_ptr<ERUSBot>(new ERUSBot(
    {Pins::Engine::left::power, Pins::Engine::left::direction::forward,
     Pins::Engine::left::direction::backward},
    {Pins::Engine::right::power, Pins::Engine::right::direction::forward,
     Pins::Engine::right::direction::backward},
    Pins::sensors));

Connection* c;

void setup() {
    std::cout << Colors::blue << "[INFO] " << Colors::reset
              << "Connecting to SSID \"" << WIFI_SSID << "\" with password\""
              << WIFI_PASSWORD << "\"" << std::endl;
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(3000);
        std::cout << Colors::red << "[ERROR] " << Colors::reset
                  << "Failed to connect to SSID \"" << WIFI_SSID
                  << "\" with password \"" << WIFI_PASSWORD << "\". Retrying..."
                  << std::endl;
    }
    std::cout << Colors::green << "[SUCCESS] " << Colors::reset
              << "Connected to WiFi" << std::endl;

    c = new Connection("192.168.0.1", 8080);
    // if (udp.listen(20001)) {
    //     printf("socket listening\n");
    //     udp.onPacket([](AsyncUDPPacket packet) {
    //         printf("got packet of size %d from %s\n", packet.length(),
    //                packet.remoteIP().toString().c_str());
    //         printf("packet contents: ");
    //         for (int i = 0; i < packet.length(); i++) {
    //             printf("%c", packet.data()[i]);
    //         }
    //         printf("\n");
    //         packet.flush();
    //     });
    // }
}

void loop() {
    // udp.broadcast("Hello, world!");
    // udp.print("Hello, world from print!");
    // udp.send("Hello, world!");
    // udp.sendTo("Hello, world!", IPAddress(192, 168, 0, 25));
    printf("broadcasting hello world\n");
    // bot.debug();
    // bot.tick();
    delay(1000);
}
