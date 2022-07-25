#ifndef NET_H
#define NET_H
#include <ArduinoJson.h>
#include <AsyncTCP.h>

using namespace std;
class Connection {
    string host;
    string port;
    AsyncClient* client;
    AsyncServer* server;

  public:
    Connection(string host, int port);
    ~Connection();
    void setHost(string host);
    void setPort(string port);
    string getHost();
    string getPort();
    void send(string message);
    void send(JsonObject& message);
};

#endif
