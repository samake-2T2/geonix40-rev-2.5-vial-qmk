/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rdr_common.h"

/********************** 시스템 함수 (System Functions) ***************************/
/* 키 매트릭스 스캔 지연 (Matrix scan key delay) */
void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}

/***************** RGB 매트릭스 드라이버 초기화 (RGB Matrix Driver Init) ********************/
led_config_t g_led_config = { {
	{ 0        , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       },
    { 12       , 13       , 14       , 15       , 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       }, 
	{ 24       , 25       , 26       , 27       , 28       , 29       , 30       , 31       , 32       , 33       , 34       , 35       }, 
	{ 36       , NO_LED   , 37       , 38       , 39       , 40       , 41       , 42       , 43       , 44       , 45       , 46       }
},{
    // 백라이트 LED (Backlight LEDs)
    { 0,  10},  { 20, 10},  { 40, 10},  { 60, 10}, { 80, 10}, { 100, 10}, { 120, 10}, { 140, 10}, { 160, 10}, { 180, 10}, { 200, 10}, { 224, 10}, 
    { 0,  20},  { 20, 20},  { 40, 20},  { 60, 20}, { 80, 20}, { 100, 20}, { 120, 20}, { 140, 20}, { 160, 20}, { 180, 20}, { 200, 20}, { 224, 20}, 
    { 0,  30},  { 20, 30},  { 40, 30},  { 60, 30}, { 80, 30}, { 100, 30}, { 120, 30}, { 140, 30}, { 160, 30}, { 180, 30}, { 200, 30}, { 224, 30}, 
    { 0,  40},  { 20, 40},  { 40, 40},  { 60, 40}, { 80, 40},             { 110, 40}, { 140, 40}, { 160, 40}, { 180, 40}, { 200, 40}, { 224, 40},

    { 255,65},  { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65},  { 255,65}, { 255,65},
    { 255,65},  { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65},  { 255,65}, { 255,65},
    { 255,65},  { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65},  { 255,65}
}, {
    // 백라이트 LED (Backlight LEDs)
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  1,  1,  1,  1,      1,  1,  1,  1,  1,  1,

    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0
} };

#include "dynamic_keymap.h"

extern bool g_remap_rf_led;

uint8_t find_rf_led_index(uint8_t index) {
    uint16_t target_kc = 0;
    switch (index) {
        case 0: target_kc = MD_USB;  break;
        case 1: target_kc = MD_BLE1; break;
        case 2: target_kc = MD_BLE2; break;
        case 3: target_kc = MD_BLE3; break;
        case 4: target_kc = MD_24G;  break;
        default: return index;
    }

    // 1. 현재 활성화된 레이어(또는 3번 레이어)에서 우선 탐색
    uint8_t active_l = get_highest_layer(layer_state);
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            if (dynamic_keymap_get_keycode(active_l, r, c) == target_kc) {
                uint8_t led = g_led_config.matrix_co[r][c];
                if (led != NO_LED) return led;
            }
        }
    }

    // 2. 3번 레이어부터 0번 레이어 순서로 탐색
    for (int l = 3; l >= 0; l--) {
        for (int r = 0; r < MATRIX_ROWS; r++) {
            for (int c = 0; c < MATRIX_COLS; c++) {
                if (dynamic_keymap_get_keycode(l, r, c) == target_kc) {
                    uint8_t led = g_led_config.matrix_co[r][c];
                    if (led != NO_LED) return led;
                }
            }
        }
    }
    return index;
}

static uint8_t find_keycode_led_index(uint16_t keycode) {
    // 1. 현재 활성 레이어에서 탐색
    uint8_t active_l = get_highest_layer(layer_state);
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            uint16_t kc = dynamic_keymap_get_keycode(active_l, r, c);
            if (kc == keycode || 
                (keycode == KC_CAPS_LOCK && kc == KC_LOCKING_CAPS_LOCK) ||
                (keycode == KC_NUM_LOCK && kc == KC_LOCKING_NUM_LOCK)) {
                uint8_t led = g_led_config.matrix_co[r][c];
                if (led != NO_LED) return led;
            }
        }
    }
    // 2. 전체 레이어(0~7) 탐색
    for (int l = 0; l <= 7; l++) {
        for (int r = 0; r < MATRIX_ROWS; r++) {
            for (int c = 0; c < MATRIX_COLS; c++) {
                uint16_t kc = dynamic_keymap_get_keycode(l, r, c);
                if (kc == keycode || 
                    (keycode == KC_CAPS_LOCK && kc == KC_LOCKING_CAPS_LOCK) ||
                    (keycode == KC_NUM_LOCK && kc == KC_LOCKING_NUM_LOCK)) {
                    uint8_t led = g_led_config.matrix_co[r][c];
                    if (led != NO_LED) return led;
                }
            }
        }
    }
    return NO_LED;
}

static uint8_t get_active_channel_target_index(void) {
    if (Keyboard_Info.Key_Mode == QMK_2P4G_MODE) {
        return 4; // 2.4G
    } else if (Keyboard_Info.Key_Mode == QMK_BLE_MODE) {
        if (Keyboard_Info.Ble_Channel == 2) {
            return 2; // BLE2
        } else if (Keyboard_Info.Ble_Channel == 3) {
            return 3; // BLE3
        } else {
            return 1; // BLE1
        }
    } else {
        return 0; // USB (QMK_USB_MODE = 2)
    }
}

static inline bool is_caps_lock_active(void) {
    return host_keyboard_led_state().caps_lock || ((Keyboard_Status.System_Led_Status & (1 << 1)) != 0);
}

static inline bool is_num_lock_active(void) {
    return host_keyboard_led_state().num_lock || ((Keyboard_Status.System_Led_Status & (1 << 0)) != 0);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool saved_fn = Key_Fn_Status;
    Key_Fn_Status = false; // 폐쇄형 라이브러리의 U/Y 상시 흰색 불 마스킹
    
    g_remap_rf_led = true; // 무선 채널 LED 동적 위치 리매핑 활성화
    User_Led_Show();
    g_remap_rf_led = false;
    
    Key_Fn_Status = saved_fn;

    // FN 활성화 시(3번 레이어 켜짐 또는 FN 누름), 현재 활성화된 무선/유선 모드 키 위치에 흰색 LED 인디케이터 점등
    if (IS_LAYER_ON(3) || get_highest_layer(layer_state) == 3 || saved_fn || Key_Fn_Status) {
        uint8_t target_idx = get_active_channel_target_index();
        uint8_t rf_led = find_rf_led_index(target_idx);
        rgb_matrix_driver.set_color(rf_led, 144, 144, 144);
    }

    // CapsLock 활성화 시 붉은색(Red) 점등 (유선/무선 공통)
    if (is_caps_lock_active()) {
        uint8_t caps_led = find_keycode_led_index(KC_CAPS_LOCK);
        if (caps_led == NO_LED) caps_led = 12; // 기본 CapsLock 위치 fallback
        rgb_matrix_driver.set_color(caps_led, 144, 0, 0); // 붉은색
    }

    // NumLock 활성화 시 노란색(Yellow) 점등 (유선/무선 공통)
    if (is_num_lock_active()) {
        uint8_t num_led = find_keycode_led_index(KC_NUM_LOCK);
        if (num_led == NO_LED) num_led = 24; // 기본 NumLock 위치 fallback
        rgb_matrix_driver.set_color(num_led, 144, 144, 0); // 노란색
    }

    // 4번 레이어(LoL 게이밍 모드) 활성화 시 전용 LED 조명 점등
    if (IS_LAYER_ON(4)) {
        // 1. 전체 키 배경 소등 (게이밍 키 강조)
        for (uint8_t i = 0; i < 47; i++) {
            rgb_matrix_driver.set_color(i, 0, 0, 0);
        }

        // 2. 주요 게이밍 키 LED 점등
        // Row 0
        rgb_matrix_driver.set_color(0,  100, 100, 100); // Tab (점수판) - 흰색
        rgb_matrix_driver.set_color(1,  0,   200, 255); // Q - 하늘색
        rgb_matrix_driver.set_color(2,  0,   200, 255); // W - 하늘색
        rgb_matrix_driver.set_color(3,  0,   200, 255); // E - 하늘색
        rgb_matrix_driver.set_color(4,  255, 0,   0);   // R (궁극기) - 빨간색
        rgb_matrix_driver.set_color(5,  0,   255, 0);   // 4 (와드) - 초록색
        rgb_matrix_driver.set_color(10, 255, 180, 0);   // P (상점) - 골드
        rgb_matrix_driver.set_color(11, 160, 32,  240); // TO(0) (탈출키) - 보라색

        // Row 1
        rgb_matrix_driver.set_color(12, 100, 100, 100); // ESC - 흰색
        rgb_matrix_driver.set_color(13, 255, 120, 0);   // A (어택) - 주황색
        rgb_matrix_driver.set_color(14, 180, 180, 50);  // S (스톱) - 연노랑
        rgb_matrix_driver.set_color(15, 255, 200, 0);   // D (스펠1 점멸) - 노란색
        rgb_matrix_driver.set_color(16, 255, 80,  0);   // F (스펠2 점화) - 주황/빨강
        rgb_matrix_driver.set_color(17, 0,   220, 220); // G (핑) - 청록색

        // Row 2
        rgb_matrix_driver.set_color(24, 100, 100, 120); // Shift - 연청
        rgb_matrix_driver.set_color(25, 220, 0,   255); // 1 (아이템1) - 마젠타
        rgb_matrix_driver.set_color(26, 220, 0,   255); // 2 (아이템2) - 마젠타
        rgb_matrix_driver.set_color(27, 220, 0,   255); // 3 (아이템3) - 마젠타
        rgb_matrix_driver.set_color(28, 255, 0,   0);   // V (백핑) - 빨간색
        rgb_matrix_driver.set_color(29, 0,   80,  255); // B (귀환) - 파란색

        // Row 3
        rgb_matrix_driver.set_color(36, 100, 100, 120); // Ctrl (스킬업) - 연청
        rgb_matrix_driver.set_color(38, 100, 100, 120); // Alt (자기시전) - 연청
        rgb_matrix_driver.set_color(41, 0,   255, 160); // Space (화면고정) - 에메랄드
    }

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // FN1(3)과 FN2(3)를 동시에 누르면 자동으로 3번 레이어(Tri-Layer) 활성화
    state = update_tri_layer_state(state, 1, 2, 3);

    // 3번 레이어가 활성화되면 자동으로 FN 상태 동기화
    Key_Fn_Status = IS_LAYER_ON_STATE(state, 3);
    return state;
}

/************************ 절전 모드 (Sleep Mode) *****************************/
static bool usb_enum_done = false;

void notify_usb_device_state_change_user(struct usb_device_state usb_device_state)
{
    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if (usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED) {
            if (!usb_enum_done) { // 첫 CONFIGURED 시 1회만 실행 (Execute once on first CONFIGURED)
                Usb_If_Ok = true;
                Usb_If_Ok_Led = true;
                Usb_If_Ok_Delay = 0;
                usb_enum_done = true; // 완료 플래그 설정 (Mark configured)
            }
        } else {
            Usb_If_Ok = false;
            Usb_If_Ok_Led = false;
            usb_enum_done = false; // 연결 해제 시 리셋 (Reset on disconnect)
        }
    } else {
        Usb_If_Ok = false;
        Usb_If_Ok_Led = false;
    }
}


void housekeeping_task_user(void) {
    User_Keyboard_Reset();
}

void board_init(void) {
    User_Keyboard_Init();
}

void keyboard_post_init_user(void) {
    User_Keyboard_Post_Init();

    // 로고 LED 기본값을 단색 흰색(White)으로 초기화
    Keyboard_Info.Logo_Mode       = LOGO_LIGHT_MODE; // 단색 상시 점등 모드
    Keyboard_Info.Logo_Colour     = 0;
    Keyboard_Info.Logo_Saturation = 255;             // 255 = White (LOGO_MIN_SATURATION)
    Keyboard_Info.Logo_Brightness = 128;             // 기본 밝기
}

void User_Consumer_Send(uint16_t Code, bool Status) {
    if (Status) {
        register_code(Code);
    } else {
        unregister_code(Code);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {   /* 키가 눌릴 때 호출되는 함수 (Called whenever a key is pressed) */
    Usb_Change_Mode_Delay = 0;                                      /* 키 입력 중 절전 모드 방지 (Prevent sleep while keys are pressed) */
    Usb_Change_Mode_Wakeup = false;

    if (record->event.pressed) {
        if (keycode == LED_RST) {
            // 1. 키보드 백라이트 RGB 초기화: 단색 하늘색 (Cyan)
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(128, 255, 128);
            eeconfig_update_rgb_matrix_default();

            // 2. 로고 LED 초기화: 단색 흰색 (White)
            Keyboard_Info.Logo_Mode       = LOGO_LIGHT_MODE;
            Keyboard_Info.Logo_Colour     = 0;
            Keyboard_Info.Logo_Saturation = 255;
            Keyboard_Info.Logo_Brightness = 128;
            Save_Flash_Set();

            return false;
        }
    }

    return Key_Value_Dispose(keycode, record);
}
