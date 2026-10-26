ESPHome component to handle LovyanGFX esp-idf devices.

For now, ESPHome mipi display extensions don't handle i80 (8 bits parallel) protocol.

Made for my own use with a JK BMS modbus, this RS485 panel board is based on a ESP32 S3 (8MB)
with a display ST7789. Full ref on the PCB is PanelLan ZX2D80CE02S-10 but its sold also as
WT32S3-28S Pro, 28 means 2.8". It may the ZX2D80CE02S-2432 suffix for the resolution 320x240.

For sure it allow also bluetooth and wifi and a few external gpios,
it's sold with wired MX connectors to use them (except the 4 pins RS485, unfortunatly).

This component was required because the ESP LovyanGFX library is hard to include in ESPHome.

This allow also to use the integrated touchscreen FT5x06 to create custom buttons and to command
the pwm backlight from ESPHome to avoid backlight when unused...

Sample yaml is based on JK BMS modbus and show the display components integration to query a few entities.

