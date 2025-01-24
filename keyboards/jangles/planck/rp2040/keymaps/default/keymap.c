// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(120, 255, 255);
//   rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT); // sets the mode to static without saving
}

enum custom_keycodes {
    GAME_MODE = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GAME_MODE:
            if (record->event.pressed) {
                    // SEND_STRING(default_layer_state);
                if (default_layer_state == 2) {
                    set_single_default_layer(0);
                    autoshift_enable();
                    rgblight_sethsv_noeeprom(120, 255, 255);
                } else {
                    set_single_default_layer(1);
                    autoshift_disable();
                    rgblight_sethsv_noeeprom(60, 255, 255);
                }
            }
            break;
    }
    return true;
}

// // Tap Dance declarations
// enum {
//     TD_ESC_TAB,
// };

// // Tap Dance definitions
// tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Tab, twice for Escape
//     [TD_ESC_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
// };

// Combos
const uint16_t PROGMEM tabesccombo[] = {KC_ESC, KC_Q, COMBO_END};
const uint16_t PROGMEM leftCurly[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM rightCurly[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM leftParen[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM rightParen[] = {KC_U, KC_SCLN, COMBO_END};
combo_t key_combos[] = {
    COMBO(tabesccombo, KC_TAB),
    COMBO(leftCurly, S(KC_LBRC)),
    COMBO(rightCurly, S(KC_RBRC)),
    COMBO(leftParen, S(KC_9)),
    COMBO(rightParen, S(KC_0))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    // Base
    [0] = LAYOUT_ortho_4x12(
        KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_BSPC,
        KC_DEL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM,    KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
        MT(MOD_LCTL, KC_HOME), KC_LWIN, MO(3),    KC_LALT,   TT(3), LT(2, KC_SPACE), TT(4), G(A(KC_K)), GAME_MODE, KC_NO, KC_NO, KC_END
    ),
    // Number
    [4] = LAYOUT_ortho_4x12(
        KC_GRAVE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_INS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_LBRC, KC_EQL,  KC_RBRC, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    // Control
    [2] = LAYOUT_ortho_4x12(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, C(KC_LEFT), C(KC_RGHT), KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        AS_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    // Function
    [3] = LAYOUT_ortho_4x12(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_TRNS, KC_TRNS, KC_WH_U, KC_MS_U, KC_WH_D, KC_TRNS, KC_TRNS,        
        KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, QK_MAKE, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT
    ),
    // Gaming 
     [1] = LAYOUT_ortho_4x12(
        KC_ESC,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_DEL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,    KC_DOT,    KC_SLSH, KC_ENT,
        KC_LCTL, KC_LWIN, MO(3),    KC_LALT,   TT(2), KC_SPACE,    TT(4), KC_BTN3,    GAME_MODE,    KC_TRNS,    KC_NO,    KC_END
    ),
};

