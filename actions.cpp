#include "actions.h"
#include "ui.h"

#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

// Ortak yardımcı fonksiyon
void sendKey(uint8_t key) {
  Keyboard.press(key);
  delay(25);                 // Host'un algılaması için yeterli süre
  Keyboard.releaseAll();
  delay(15);                 // İki tuş arasında kısa boşluk
}

void action_b1_action(lv_event_t* e) {
  sendKey(KEY_BACKSPACE);    // BACKSPACE
}

void action_b2_action(lv_event_t* e) {
  sendKey(KEY_BACKSPACE);    // BACKSPACE
}

void action_b3_action(lv_event_t* e) {
  sendKey('3');
}

void action_b4_action(lv_event_t* e) {
  sendKey('4');
}

void action_b5_action(lv_event_t* e) {
  sendKey('5');
}

void action_b6_action(lv_event_t* e) {
  sendKey('6');
}