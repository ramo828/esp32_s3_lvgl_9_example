#include "touch_driver.h"

FT6336G_t touch = {
  .rotation = 0,
  .screen_w = 240,
  .screen_h = 320,
  .last_x = 0,
  .last_y = 0,
  .debug = false
};

static bool FT6336G_readRegister(uint8_t reg, uint8_t *buffer, uint8_t length) {
  Wire.beginTransmission(FT6336_ADDR);
  Wire.write(reg);

  if (Wire.endTransmission(false) != 0)
    return false;

  uint8_t received = Wire.requestFrom((int)FT6336_ADDR, (int)length);
  if (received != length) {
    while (Wire.available()) {
      Wire.read();
    }
    return false;
  }

  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }

  return true;
}

bool FT6336G_begin(void) {
  pinMode(TOUCH_RST, OUTPUT);
  digitalWrite(TOUCH_RST, LOW);
  delay(20);
  digitalWrite(TOUCH_RST, HIGH);
  delay(300);

  pinMode(TOUCH_INT, INPUT_PULLUP);

  Wire.begin(TOUCH_SDA, TOUCH_SCL);
  Wire.setClock(400000);

  Wire.beginTransmission(FT6336_ADDR);
  uint8_t error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("FT6336G bulundu.");
    return true;
  }

  Serial.print("FT6336G bulunamadi! Hata: ");
  Serial.println(error);
  return false;
}

bool FT6336G_readRaw(uint16_t *x, uint16_t *y) {
  uint8_t touch_count = 0;
  if (!FT6336G_readRegister(FT6336_REG_TOUCH_COUNT, &touch_count, 1))
    return false;

  if (touch_count == 0)
    return false;

  uint8_t data[4];
  if (!FT6336G_readRegister(FT6336_REG_TOUCH_DATA, data, 4))
    return false;

  *x = ((uint16_t)(data[0] & 0x0F) << 8) | data[1];
  *y = ((uint16_t)(data[2] & 0x0F) << 8) | data[3];

  if (*x >= 240 || *y >= 320)
    return false;

  return true;
}

void FT6336G_setRotation(uint8_t rotation) {
  touch.rotation = rotation;
}

void FT6336G_setScreenSize(uint16_t width, uint16_t height) {
  touch.screen_w = width;
  touch.screen_h = height;
}

void FT6336G_setDebug(bool enable) {
  touch.debug = enable;
}

void FT6336G_transform(uint16_t raw_x, uint16_t raw_y,
                       uint16_t *screen_x, uint16_t *screen_y) {
  if (touch.screen_w == 320 && touch.screen_h == 240) {

    // =========================
    // YATAY / LANDSCAPE
    // =========================
    //
    // RAW Y -> LVGL X
    // RAW X -> LVGL Y (ters)
    //
    // Daha once 4 kose testinde
    // bu mapping dogru cikti.

    *screen_x = raw_y;
    *screen_y = 239 - raw_x;
  } else if (touch.screen_w == 240 && touch.screen_h == 320) {

    // =========================
    // DIKEY / PORTRAIT
    // =========================
    //
    // RAW X -> LVGL X
    // RAW Y -> LVGL Y
    //
    // Dikey mod 4 kose kalibrasyonu:
    //
    // RAW X:
    // Sol  ~36
    // Sag  ~228
    //
    // RAW Y:
    // Ust  ~23
    // Alt  ~292

    *screen_x = map(raw_x, 36, 228, 0, 239);
    *screen_y = map(raw_y, 23, 292, 0, 319);
  } else {

    // Beklenmeyen ekran boyutu
    *screen_x = raw_x;
    *screen_y = raw_y;
  }

  // =========================
  // SINIRLAR
  // =========================

  if (*screen_x >= touch.screen_w)
    *screen_x = touch.screen_w - 1;

  if (*screen_y >= touch.screen_h)
    *screen_y = touch.screen_h - 1;
}

void FT6336G_readCallback(lv_indev_t *indev, lv_indev_data_t *data) {
  uint16_t raw_x, raw_y;

  if (FT6336G_readRaw(&raw_x, &raw_y)) {
    uint16_t screen_x, screen_y;
    FT6336G_transform(raw_x, raw_y, &screen_x, &screen_y);

    touch.last_x = screen_x;
    touch.last_y = screen_y;

    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = screen_x;
    data->point.y = screen_y;

    if (touch.debug) {
      Serial.printf("TOUCH RAW: %d,%d  -> LVGL: %d,%d\n",
                    raw_x, raw_y, screen_x, screen_y);
    }
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
    data->point.x = touch.last_x;
    data->point.y = touch.last_y;
  }
}