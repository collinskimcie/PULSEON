# PULSEON Watch UI

This LVGL Pro project is the editable source for the watch UI. The target is a
240 × 320 ESP32-S3 display running LVGL 9.5.0.

Edit the screens, components, and assets here. PlatformIO consumes this project
directly through the local library dependency in
[`PULSEON_FIRMWARE/platformio.ini`](../PULSEON_FIRMWARE/platformio.ini), so UI
source no longer needs to be copied into the firmware tree.

The running watch interface is assembled by the firmware in
[`UIManager.cpp`](../PULSEON_FIRMWARE/src/ui/UIManager.cpp); the LVGL Pro project
provides the generated UI library and editor assets used by the firmware.

## Project contents

- `screens/` — screen definitions and generated C sources
- `components/` — reusable controls, layout, list, image, and typography components
- `images/` and `fonts/` — UI assets and generated font data
- `sim/` — LVGL Pro simulator sources
- `tests/` — UI editor test definitions

Open this directory in LVGL Pro to edit the project. Generated preview and
PlatformIO build files are local outputs and can be recreated.
