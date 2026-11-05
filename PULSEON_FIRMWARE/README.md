# PULSEON Firmware

Smartwatch firmware for the Viewe UEDX24320028E-WB-A (ESP32-S3, 2.8" 240x320 touch display).
Arduino framework on PlatformIO, LVGL 9.5, NimBLE, and a vendored ChronosESP32 so the watch
pairs with the Chronos phone app.

## Features
- Home faces, themes, and a launcher with tiles
- Chronos integration: notifications, music controls, weather, navigation, find phone, camera, calls
- Alarms with an on-watch editor (edits are saved to NVS and survive reboots and phone syncs)
- Today dashboard (weather, steps, alerts, next alarm)
- Display dim/off with wake on calls, alarms and events
- Wi-Fi OTA updates with rollback

## Build and flash
    cp include/wifi_secrets.h.example include/wifi_secrets.h   # then edit it
    pio run                      # build
    pio run -t upload            # flash over USB
    pio device monitor           # serial log, 115200 baud

The UI library is the sibling folder `../PULSEON_WATCH_UI` (a `file://` lib_dep), so keep both
folders side by side.

## Wireless upload
    export PULSEON_OTA_PASS=<OTA_PASSWORD from wifi_secrets.h>
    pio run -e esp32-s3-ota -t upload

## Environments
- `esp32-s3-dev`: default development build
- `esp32-s3-ota`: wireless upload
- `esp32-s3-release`: battery build without always-on Wi-Fi

`include/wifi_secrets.h` is gitignored. Never commit it.
