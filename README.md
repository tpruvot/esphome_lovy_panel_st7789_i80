ESPHome component to handle LovyanGFX esp-idf devices.
---

For now, ESPHome mipi display extensions don't handle i80 (8 bits parallel) protocol.

Made for my own use with a JK BMS modbus, this RS485 panel board is based on a ESP32 S3 (8MB)
with a display ST7789. Full ref on the PCB is PanelLan ZX2D80CE02S-10 but its sold also as
WT32S3-28S Pro, 28 means 2.8". It may be seen with the 2432 suffix for the resolution 320x240.

For sure it allow also bluetooth and wifi and a few external gpios,
it's sold with wired MX connectors to use them (except the 4 pins RS485, unfortunately).

This component was required because the ESP LovyanGFX library is hard to include in ESPHome.

This allow also to use the integrated touchscreen FT5x06 to create custom buttons and to command
the pwm backlight from ESPHome, to avoid backlight when unused...

Sample yaml is based on JK BMS modbus and show the display components integration to query a few entities.

<img width="594" height="406" alt="WT32S3-JK-PB2A16S" src="https://github.com/user-attachments/assets/e091975c-6f57-436e-825c-78eeab21cca2" />

Links
-----

Datasheet: https://scribd.com/document/950059125/WT32S3-28S-PRO-ZX2D80CE02S-V1-0-EN-Datasheet

- https://github.com/lovyan03/LovyanGFX
- https://components.espressif.com/components/espressif/esp_lcd_panel_io_additions/versions/1.0.1~1/readme
- https://github.com/syssi/esphome-jk-bms
- https://doc.panel-tag.cn/ESP32-S3/index.html
- https://github.com/smartpanle/QMSD-ESP32-BSP
- https://gitee.com/qiming-zhixian/qmsd-esp32-bsp
- https://www.buydisplay.com/download/ic/ST7789.pdf

Special thanks to google A.I mode who helped me with ESPHome components creation... in parallel...
