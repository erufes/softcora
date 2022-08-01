#include "net.h"
#include "../../include/secrets.h"
#include "../../include/utils.h"
#include "WiFi.h"
#include <iostream>

Connection::Connection(string host, int port) {
    this->host = host;
    this->port = port;
    this->client = new AsyncClient();
    this->server = new AsyncServer(IPAddress(127, 0, 0, 1), 8080);
    while (!this->client->connected()) {
        this->client->connect(host.c_str(), port);
        printf("\n connecting to %s on port %d \n", host.c_str(), port);
        delay(1000);
    }
}

Connection::~Connection() {
    this->client->close();
    this->server->end();
    free(this->client);
    free(this->server);
}

void Connection::setHost(string host) { this->host = host; }

void Connection::setPort(string port) { this->port = port; }

string Connection::getHost() { return this->host; }

string Connection::getPort() { return this->port; }

void Connection::send(string message) {
    if (this->client->connected()) {
        this->client->add(message.c_str(), message.length());
        this->client->send();
    }
}

void Connection::send(JsonObject& message) {
    if (this->client->connected()) {
        char buffer[256];
        size_t size = serializeJson(message, buffer, sizeof(buffer));
        this->client->add(buffer, size);
        this->client->send();
    }
}

void Connection::setupWirelessConnection() {
    std::cout << Colors::blue << "[INFO] " << Colors::reset
              << "Connecting to SSID \"" << WIFI_SSID << "\" with password\""
              << WIFI_PASSWORD << "\"" << std::endl;
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(3000);
        std::cout << Colors::red << "[ERROR] " << Colors::reset
                  << "Failed to connect to SSID \"" << WIFI_SSID
                  << "\" with password \"" << WIFI_PASSWORD
                  << "\". Retrying... " << std::endl;
    }
    printf("\n connected to WiFi \n");
    std::cout << Colors::green << "[SUCCESS] " << Colors::reset
              << "Connected to WiFi" << std::endl;
}