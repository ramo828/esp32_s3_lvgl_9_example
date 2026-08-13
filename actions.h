#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>
#include "screens.h"

#ifdef __cplusplus
#include "USB.h"
#include "USBHIDKeyboard.h"

extern USBHIDKeyboard Keyboard;   // Sadece bildirim (tanım actions.cpp'te olacak)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void action_b1_action(lv_event_t * e);
void action_b2_action(lv_event_t * e);
void action_b3_action(lv_event_t * e);
void action_b4_action(lv_event_t * e);
void action_b5_action(lv_event_t * e);
void action_b6_action(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/