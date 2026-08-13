#include <lvgl.h>
#include "ui.h"
#include "touch_driver.h"
#include "display_manager.h"

unsigned long last_tick = 0;
static lv_chart_series_t* ser = NULL;

// Task ile loop arasında paylaşılacak veri
static volatile int chart_value = 0;
static volatile bool chart_ready = false;

#define CHART_STACK_SIZE 4096   // 10KB fazla, 4KB yeterli

static StackType_t chartStack[CHART_STACK_SIZE];
static StaticTask_t chartTaskBuffer;

// Sadece veri üreten task (LVGL çağrısı YOK)
void chart_task(void* vParam) {
  while (true) {
    chart_value = random(0, 100);   // sensörün yerine
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// Chart ayarlarını setup içinde yap (ui_init sonrası)
void chart_init() {
  if (objects.chart == NULL) {
    Serial.println("HATA: objects.chart bulunamadi!");
    return;
  }

  lv_chart_set_type(objects.chart, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(objects.chart, 50);
  lv_chart_set_range(objects.chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
  lv_chart_set_update_mode(objects.chart, LV_CHART_UPDATE_MODE_SHIFT);

  ser = lv_chart_add_series(objects.chart, lv_color_hex(0x00FF00), LV_CHART_AXIS_PRIMARY_Y);
  chart_ready = true;

  Serial.println("Chart hazir.");
}

void setup() {
  Serial.begin(115200);
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

  // Chart'ı UI hazır olduktan sonra kur
  chart_init();

  // Task'ı oluştur
  xTaskCreateStaticPinnedToCore(
    chart_task,
    "Chart",
    CHART_STACK_SIZE,
    NULL,
    1,
    chartStack,
    &chartTaskBuffer,
    0
  );

  Serial.println("SISTEM HAZIR");
}

void loop() {
  unsigned long now = millis();

  if (now - last_tick >= 5) {
    lv_tick_inc(now - last_tick);
    last_tick = now;
  }

  // LVGL güncellemeleri sadece burada (güvenli)
  if (chart_ready && ser != NULL) {
    lv_chart_set_next_value(objects.chart, ser, chart_value);
  }

  lv_timer_handler();
  delay(5);
}