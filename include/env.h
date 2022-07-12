#ifndef ENV_H
#define ENV_H
#include "utils.h"
#include <cstdio>

#ifndef WIFI_PASSWORD
#warning                                                                       \
    "WIFI_PASSWORD not defined, using default value. Please export it from CLI before build."
#define WIFI_PASSWORD "default password"
#endif

#ifndef WIFI_SSID
#warning                                                                       \
    "WIFI_SSID not defined, using default value. Please export it from CLI before build."
#define WIFI_SSID "default ssid"
#endif

#endif