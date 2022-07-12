#!/bin/bash

# EDIT THIS SECTION
SSID="ssid"
PASSWORD="password"


##################################
# DO NOT EDIT BELOW THIS LINE!
##################################
RED="\e[31m"
ENDCOLOR="\e[0m"
GREEN="\e[32m"

if [[ "$SSID" == "" ]]; then
    echo -e "${RED}[ERROR]${ENDCOLOR} Please setup SSID at env.sh"
    exit 1
fi

if [[ "$PASSWORD" == "" ]]; then
    echo -e "${RED}[ERROR]${ENDCOLOR} Please setup PASSWORD at env.sh"
    exit 1
fi

export WIFI_SSID="$SSID"
export WIFI_PASSWORD="$PASSWORD"

echo -e "${GREEN}[SUCCESS]${ENDCOLOR} Wireless settings set."