#pragma once

#include <Arduino.h>

// Saved Wi-Fi networks and the phone setup page.
void wifiConnectBegin();
bool wifiConnectAdvance();
void wifiSetupStart();
void wifiSetupLoop();
bool wifiSetupSaved();
void wifiSetupStop();
const char* wifiSetupHelp();
