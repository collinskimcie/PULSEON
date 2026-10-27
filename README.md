# PULSEON

**An ESP32-S3 smartwatch firmware and LVGL-based user interface project.**

PULSEON is an embedded smartwatch project built around ESP32 hardware, LVGL, and the ChronosESP32 library. It combines a graphical watch interface with firmware intended to support smartwatch functionality and hardware integration.

> **Development status:** Active development. The firmware compiles successfully, but display operation, touch input, and navigation must be verified on the physical device.

## Features

- LVGL 9.5.0 graphical interface
- 240 × 320 portrait watch display layout
- ESP32-S3 firmware built with PlatformIO and Arduino
- Generated watch UI screens
- ChronosESP32 integration
- NimBLE-Arduino dependency for Bluetooth Low Energy functionality
- ESP32 display and I/O expander library integration
- Modular firmware and UI project structure
- Built-in mock health data for UI demonstrations, enabled by default

Set `PULSEON_DEMO_MODE` to `0` in `PULSEON_FIRMWARE/include/app_config.h` to
show sensor-unavailable states instead of mock readings. Any non-zero sensor
values supplied by the app state take precedence over the mock data.

The six selectable home faces are Brutalist V2, Dot Matrix V2, Topo V2,
Glassmorph V2, Circuit Blueprint, and Holographic Prism. Their circular
designs are clipped to the circular watch area on the 240 × 320 portrait
display, without a PulseOn wordmark; app screens and swipe navigation are
unchanged.

### Watch UI screens

The current UI project contains seven screens:

| Screen | Purpose |
|---|---|
| WatchHome | Main watch face |
| QuickControls | Quick-access controls |
| Health | Health and activity interface |
| Notifications | Notification interface |
| Music | Music controls interface |
| Settings | Watch settings |
| Weather | Weather interface |

Some screens and data fields may still require firmware integration and testing on the target hardware.

## Technology Stack

- **Microcontroller:** ESP32-S3
- **Framework:** Arduino
- **Build system:** PlatformIO
- **Graphics:** LVGL 9.5.0
- **UI design:** LVGL Pro Editor
- **Bluetooth:** NimBLE-Arduino
- **Watch integration:** ChronosESP32
- **Language:** C++17

## Repository Structure

```text
PULSEON/
├── PULSEON_FIRMWARE/
│   ├── include/
│   ├── lib/              # Firmware-local libraries and board support
│   ├── src/
│   └── platformio.ini
├── PULSEON_WATCH_UI/     # Canonical LVGL Pro UI source
├── vendor/               # Upstream library submodules
│   ├── ESP32_Display_Panel/
│   └── ESP32_IO_Expander/
└── README.md
```

The firmware consumes `PULSEON_WATCH_UI` as a local PlatformIO dependency, so
there is only one editable copy of the UI. PlatformIO dependencies and build
outputs are regenerated under the ignored `.pio/` directory.

## Wi-Fi and wireless updates

### Setup

1. Copy the template and fill in your network and an OTA password:

   ```bash
   cp include/wifi_secrets.h.example include/wifi_secrets.h
   ```

   `include/wifi_secrets.h` is git-ignored, so the real passwords stay local. The Wi-Fi must be 2.4 GHz.
2. Flash once over USB: `./flash.sh`

### Status icons

Small Bluetooth and Wi-Fi symbols appear at the top right of every screen while the phone (Chronos app) is connected and while the watch is online.

### Wi-Fi behavior

- After boot the watch joins its saved networks in order, then the one in `wifi_secrets.h`. Each gets about 20 seconds. If none works it retries after 60 seconds.
- The OTA service runs whenever the watch is online. Set `KEEP_WIFI_ON` to `false` in `src/ui/UIManager.cpp` to use Wi-Fi only while Apps > Update is open (better battery life, and Wi-Fi and Bluetooth share one radio).
- If no network joins from the Update page, the watch opens its own network `PULSEON-Setup` (password `pulseon1`). Join it from a phone, open `http://192.168.4.1`, and save a network. Up to 5 networks are stored on the watch.

### Wireless update

1. Make sure the PC is on the same network as the watch.
2. Run `./ota.sh <watch-ip>`. The watch prints its IP in the serial monitor (`[WIFI] keep-alive: online, IP ...` or `[UPDATE] ready, IP ...`).
3. The watch reboots by itself. About 30 seconds later the monitor shows `[OTA] firmware marked valid: ESP_OK`. A firmware that crashes before that point rolls back to the previous version.

### Limits

- Networks with a browser login page (captive portal) or username-and-password login (WPA2-Enterprise) cannot be joined.
- Some networks block devices from talking to each other (client isolation). Wireless updates fail there; use USB or a phone hotspot.
