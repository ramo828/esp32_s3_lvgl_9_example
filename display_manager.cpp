#include "display_manager.h"
#include "screens.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "touch_driver.h"

#if LANDSCAPE == 1
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#else
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#endif

#define BUFFER_LINES 40

TFT_eSPI tft = TFT_eSPI();

lv_display_t *disp = nullptr;
lv_indev_t *indev = nullptr;
lv_color_t *disp_buf = nullptr;


void flush_cb(
  lv_display_t *display,
  const lv_area_t *area,
  uint8_t *px_map) {
  uint32_t w = (uint32_t)(area->x2 - area->x1 + 1);
  uint32_t h = (uint32_t)(area->y2 - area->y1 + 1);

  // RGB565 byte swap
  uint16_t *buf = (uint16_t *)px_map;
  uint32_t pixels = w * h;

  for (uint32_t i = 0; i < pixels; i++) {
    buf[i] = (buf[i] >> 8) | (buf[i] << 8);
  }

  tft.pushImage(area->x1, area->y1, w, h, buf);

  lv_display_flush_ready(display);
}


bool initDisplay() {
  tft.begin();

#if LANDSCAPE == 1
  tft.setRotation(1);
#else
  tft.setRotation(0);
#endif

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  tft.fillScreen(TFT_BLACK);
  delay(100);

  Serial.printf(
    "LCD: %dx%d\n",
    tft.width(),
    tft.height());

  Serial.println("LCD hazir.");

  return true;
}


bool initLVGLDisplay() {
  lv_init();

  size_t buffer_pixels =
    (size_t)SCREEN_WIDTH * BUFFER_LINES;

  size_t buffer_bytes =
    buffer_pixels * sizeof(lv_color_t);

  disp_buf = (lv_color_t *)malloc(buffer_bytes);

  if (!disp_buf) {
    Serial.println("HATA: LVGL buffer ayrilamadi!");
    return false;
  }

  disp = lv_display_create(
    SCREEN_WIDTH,
    SCREEN_HEIGHT);

  if (!disp) {
    Serial.println(
      "HATA: LVGL display olusturulamadi!");

    free(disp_buf);
    disp_buf = nullptr;

    return false;
  }

  lv_display_set_color_format(
    disp,
    LV_COLOR_FORMAT_RGB565);

  lv_display_set_flush_cb(
    disp,
    flush_cb);

  lv_display_set_buffers(
    disp,
    disp_buf,
    NULL,
    buffer_bytes,
    LV_DISPLAY_RENDER_MODE_PARTIAL);

  Serial.println("LVGL display hazir.");

  return true;
}


bool initLVGLTouch() {
  // FT6336G_setRotation(0);

  FT6336G_setScreenSize(
    SCREEN_WIDTH,
    SCREEN_HEIGHT);

  FT6336G_setDebug(true);

  indev = lv_indev_create();

  if (!indev) {
    Serial.println(
      "HATA: LVGL input device olusturulamadi!");

    return false;
  }

  lv_indev_set_type(
    indev,
    LV_INDEV_TYPE_POINTER);

  lv_indev_set_read_cb(
    indev,
    FT6336G_readCallback);

  Serial.println("LVGL touch hazir.");

  return true;
}

