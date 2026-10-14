# PULSEON

**An ESP32-S3 smartwatch firmware and LVGL-based user interface project.**

PULSEON is an embedded smartwatch project built around ESP32 hardware, LVGL, and the ChronosESP32 library. It combines a graphical watch interface with firmware intended to support smartwatch functionality and hardware integration.

> **Development status:** Active development. The firmware compiles successfully, but display operation, touch input, and navigation must be verified on the physical device.

## Features

- LVGL 9.5.0 graphical interface
- 320 × 240 watch display layout
- ESP32-S3 firmware built with PlatformIO and Arduino
- Generated watch UI screens
- ChronosESP32 integration
- NimBLE-Arduino dependency for Bluetooth Low Energy functionality
- ESP32 display and I/O expander library integration
- Modular firmware and UI project structure

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
│   ├── lib/
│   │   └── PULSEON_WATCH_UI/
│   ├── src/
│   └── platformio.ini
├── PULSEON_WATCH_UI/
├── vendor/
│   ├── ESP32_Display_Panel/
│   └── ESP32_IO_Expander/
└── README.md
