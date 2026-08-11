#ifndef TOUCH_DRIVER_H
#define TOUCH_DRIVER_H

#include <Arduino.h>
#include <Wire.h>
#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TOUCH_SDA   16
#define TOUCH_SCL   15
#define TOUCH_RST   18
#define TOUCH_INT   17
#define FT6336_ADDR 0x38

#define FT6336_REG_TOUCH_COUNT  0x02
#define FT6336_REG_TOUCH_DATA   0x03

typedef struct {
    uint8_t  rotation;
    uint16_t screen_w;
    uint16_t screen_h;
    uint16_t last_x;
    uint16_t last_y;
    bool     debug;
} FT6336G_t;

extern FT6336G_t touch;

bool FT6336G_begin(void);
bool FT6336G_readRaw(uint16_t *x, uint16_t *y);
void FT6336G_setRotation(uint8_t rotation);
void FT6336G_setScreenSize(uint16_t width, uint16_t height);
void FT6336G_setDebug(bool enable);
void FT6336G_transform(uint16_t raw_x, uint16_t raw_y, uint16_t *screen_x, uint16_t *screen_y);
void FT6336G_readCallback(lv_indev_t *indev, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif

#endif