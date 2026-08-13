#include <lvgl.h>
#include "ui.h"
#include "touch_driver.h"
#include "display_manager.h"
#include "actions.h"
#include <USB.h>
#include <USBHIDKeyboard.h>

long unsigned int last_tick = 0;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  USB.begin();
  delay(500);

  if (!initDisplay()) {
    Serial.println("LCD baslatilamadi!");
    while (true) delay(1000);
  }

  if (!FT6336G_begin()) {
    Serial.println("UYARI: Touch bulunamadi, ekran devam ediyor.");
  }

  if (!initLVGLDisplay()) {
    Serial.println("LVGL display baslatilamadi!");
    while (true) delay(1000);
  }

  if (!initLVGLTouch()) {
    Serial.println("LVGL touch baslatilamadi!");
    while (true) delay(1000);
  }

  Serial.println("UI baslatiliyor...");
  ui_init();
  lv_timer_handler();

  Serial.println("SISTEM HAZIR");
}

void loop() {
  unsigned long now = millis();

  if (now - last_tick >= 5) {
    lv_tick_inc(now - last_tick);
    last_tick = now;
  }

  lv_timer_handler();
  delay(5);
}