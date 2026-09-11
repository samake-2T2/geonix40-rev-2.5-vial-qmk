/* Copyright 2021 QMK
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

#pragma once

#define VIAL_KEYBOARD_UID { 0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x11, 0x22 }

#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define VIAL_COMBO_ENTRIES 4
#define VIAL_TAP_DANCE_ENTRIES 4
#define VIAL_KEY_OVERRIDE_ENTRIES 0
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  1151

/* Macro & Tap code delay (무선 송신 버퍼 오버플로 방지 지연 시간) */
#define TAP_CODE_DELAY 10
#define DYNAMIC_KEYMAP_MACRO_DELAY 50

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 1152
#endif

#ifndef FEE_PAGE_SIZE
#define FEE_PAGE_SIZE (0x200)
#endif
#ifndef FEE_PAGE_COUNT
#define FEE_PAGE_COUNT (8)
#endif

#ifndef FEE_PAGE_BASE_ADDRESS
#define FEE_PAGE_BASE_ADDRESS (0x1F000)
#endif
#ifndef FEE_MCU_FLASH_SIZE
#define FEE_MCU_FLASH_SIZE (0x1000)
#endif

#ifndef EECONFIG_USER_DATA_SIZE
#define EECONFIG_USER_DATA_SIZE 4
#endif

#ifndef EECONFIG_KB_DATA_SIZE
#define EECONFIG_KB_DATA_SIZE 1
#endif

#ifndef TRANSIENT_EEPROM_SIZE
#define TRANSIENT_EEPROM_SIZE 4096
#endif

