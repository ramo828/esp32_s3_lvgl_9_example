#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MY_SCREEN = 1,
    SCREEN_ID_SETTINGS = 2,
    _SCREEN_ID_LAST = 2
};

typedef struct _objects_t {
    lv_obj_t *my_screen;
    lv_obj_t *settings;
    lv_obj_t *chart;
    lv_obj_t *exit;
} objects_t;

extern objects_t objects;

void create_screen_my_screen();
void tick_screen_my_screen();

void create_screen_settings();
void tick_screen_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/