#include QMK_KEYBOARD_H
#include "naginata.h"

enum layer_names {
  _BASE = 0,
  _NAGI,
};

// まずは確実に「1キーで」薙刀ON/OFF（コンボは後で）
enum custom_keycodes {
  NG_TOG = NG_SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_naginata(keycode, record)) return false;

  switch (keycode) {
    case NG_TOG:
      if (record->event.pressed) {
        if (naginata_state()) {
          naginata_off();
          layer_off(_NAGI);
        } else {
          naginata_on();
          layer_on(_NAGI);
        }
      }
      return false;
  }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Corne: 中央4キーなし → LAYOUT_split_3x6_3
  [_BASE] = LAYOUT_split_3x6_3(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,           KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,
    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,           KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, KC_BSLS,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,           KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_MINS, KC_EQL,
                              NG_TOG, KC_SPC, KC_ENT,       KC_BSPC, KC_TAB, KC_ESC
  ),

  // 薙刀レイヤ（まずは同じ位置に NG_ を並べる）
  [_NAGI] = LAYOUT_split_3x6_3(
    NG_Q,   NG_W,   NG_E,   NG_R,   NG_T,   NG_Y,           NG_U,   NG_I,   NG_O,   NG_P,   KC_LBRC, KC_RBRC,
    NG_A,   NG_S,   NG_D,   NG_F,   NG_G,   NG_H,           NG_J,   NG_K,   NG_L,   NG_SCLN,KC_QUOT, KC_BSLS,
    NG_Z,   NG_X,   NG_C,   NG_V,   NG_B,   NG_N,           NG_M,   NG_COMM,NG_DOT, NG_SLSH,KC_MINS, KC_EQL,
                              NG_TOG, KC_SPC, KC_ENT,       KC_BSPC, KC_TAB, KC_ESC
  ),
};
