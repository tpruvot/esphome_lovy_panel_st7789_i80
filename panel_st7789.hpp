#pragma once
#define LGFX_USE_V1
#define LGFX_AUTODETECT

#include "esphome/core/component.h"
#include <LovyanGFX.hpp>
#include <functional>

namespace lovy_panel_st7789_i80 {

class Panel_ST7789_I80 : public esphome::PollingComponent, public lgfx::LGFX_Device {

  lgfx::Panel_ST7789  _panel_instance;
  lgfx::Bus_Parallel8 _bus_instance;
  lgfx::Touch_FT5x06  _touch_instance;

  volatile bool touch_triggered_{false};
  lgfx::v1::touch_point_t points[3];

  static void IRAM_ATTR on_touch_isr(void* arg) {
    auto* instance = static_cast<Panel_ST7789_I80*>(arg);
    instance->touch_triggered_ = true;
  }

  std::function<void(Panel_ST7789_I80*)> writer_f_{nullptr};

public:

  bool touched = false;
  lgfx::v1::touch_point_t tp;

  //lgfx::Font_TTF font_roboto;
  //lgfx::Font_TTF font_icons;

  Panel_ST7789_I80() : esphome::PollingComponent(100)
  {
    {
      auto cfg = _bus_instance.config();

      cfg.port = 0;              // LCD_CAM ESP32-S3
      cfg.freq_write = 20000000; // 20 MHz

      cfg.pin_wr = GPIO_NUM_17;  // WR
      cfg.pin_rd = -1;           // RD always on
      cfg.pin_rs = GPIO_NUM_18;  // RS / DC

      cfg.pin_d0 = GPIO_NUM_16; cfg.pin_d1 = GPIO_NUM_40;
      cfg.pin_d2 = GPIO_NUM_15; cfg.pin_d3 = GPIO_NUM_7;
      cfg.pin_d4 = GPIO_NUM_41; cfg.pin_d5 = GPIO_NUM_42;
      cfg.pin_d6 = GPIO_NUM_2;  cfg.pin_d7 = GPIO_NUM_1;

      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs           = -1;
      cfg.pin_rst          = GPIO_NUM_3;  // RST
      //cfg.pin_bl         = GPIO_NUM_47; // Backlight in ESPHome
      //cfg.pin_te         = GPIO_NUM_38; // Frame synch interrupt
      cfg.invert           = true;

      cfg.panel_width      = 240;
      cfg.panel_height     = 320;
      cfg.memory_width     = 240;
      cfg.memory_height    = 320;
      cfg.bus_shared       = false;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _touch_instance.config();
      cfg.x_min      = 0;
      cfg.x_max      = 240;
      cfg.y_min      = 0;
      cfg.y_max      = 320;
      cfg.bus_shared = false;

      cfg.pin_sda    = GPIO_NUM_8;   // TP_SDA
      cfg.pin_scl    = GPIO_NUM_9;   // TP_SCL
      cfg.pin_int    = GPIO_NUM_48;  // TP_INT
      cfg.pin_rst    = -1;           // GPIO_NUM_3 TP_RST shared with display

      cfg.freq       = 400000;       // I2C Fast Mode : 400 kHz
      cfg.i2c_addr   = 0x38;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
    setPanel(&_panel_instance);
  }

  void setup() override {
    init();
    setRotation(3); // Landscape
    fillScreen(TFT_BLACK);

    // touch screen interrupt
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_48);
    io_conf.mode = GPIO_MODE_INPUT;             // Mode Entrée
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;    // Pull-Up resistor
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_48, on_touch_isr, (void*)this);

    //todo: font_roboto.loadFont("/spiffs/roboto.ttf");
    //font_icons.loadFont("/spiffs/icons_16.ttf");
  }

  // link the lambda
  void set_writer(std::function<void(Panel_ST7789_I80*)> writer_f) {
    this->writer_f_ = std::move(writer_f);
  }

  void update() override {
    // lambda 'it'
    if (this->writer_f_ != nullptr) {
      this->writer_f_(this);
    }
  }

  void loop() override {
    if (this->touch_triggered_) {
      this->touch_triggered_ = false;
      uint_fast8_t res = _touch_instance.getTouchRaw(&points[0], 1);
      if (res > 0) {
        this->touched = true;
        tp = points[0];
        tp.x = tp.y; tp.y = points[0].x;
        ESP_LOGD("ST7789", "touch at %d/%d", tp.x, tp.y);
        this->update();
        this->touched = false;
      }
    }
  }

};

// sprite buffer to reduce flickering
extern lgfx::LGFX_Sprite canvas;

} // namespace lovy_panel_st7789_i80
