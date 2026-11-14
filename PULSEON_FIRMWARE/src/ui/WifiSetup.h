#pragma once

#include <Arduino.h>

// Saved Wi-Fi networks and the phone setup page.
void wifiConnectBegin();
bool wifiConnectAdvance();
int8_t wifiScanPoll();
uint32_t wifiRetryDelayMs();
void wifiBackoffGrow();
void wifiBackoffReset();
void wifiSetupStart();
void wifiSetupLoop();
bool wifiSetupSaved();
void wifiSetupStop();
const char* wifiSetupHelp();
