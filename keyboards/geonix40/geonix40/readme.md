# GEONIX40 (Rev.2.5) — Hardware & Firmware Specifications

GEONIX40 (Rev.2.5) Tri-Mode (USB / Bluetooth 5.0 / 2.4GHz RF) 40% Ortholinear Mechanical Keyboard.  
(GEONIX40 Rev.2.5 삼중 모드 유무선 40% 직교 배열 기계식 키보드)

---

## 🔬 Hardware Specifications (하드웨어 명세)

* **MCU**: Eastsoft (上海东软载波) **ES32FS026** (32-bit ARM Cortex-M0 @ 48MHz~72MHz)
* **Wireless SoC**: **91680** (YC91680 / RDM026 Module, SPI Interface with MCU)
* **Memory**:
  - Flash: **128 KB** (ROM)
  - SRAM: **16 KB** (RAM)
  - Emulated EEPROM: **1,152 Bytes** (Hard limit defined by proprietary blob)
* **Connectivity**: USB-C Wired, Bluetooth 5.0 LE (3 Channels: BLE1, BLE2, BLE3), 2.4GHz RF
* **Matrix (4 Rows × 12 Cols, ROW2COL)**:
  - Row Pins: `B0`, `B4`, `B5`, `B6`
  - Col Pins: `D15`, `D14`, `C15`, `C14`, `C13`, `D3`, `D2`, `C12`, `C11`, `C10`, `A14`, `C9`
* **Lighting (총 76개 WS2812 RGB LED)**:
  - 47 Per-key Switch RGB LEDs
  - 29 Side & Logo Ambient RGB LEDs
* **USB VID / PID**: `0x36B0` / `0x313B`
* **Battery**: LiPo with 12-bit ADC monitoring (Pin `A13`), 2-Stage Auto Sleep

---

## ⚡ Firmware & Macro Optimizations (최적화 내역)

* **Wireless Macro Delay**: `DYNAMIC_KEYMAP_MACRO_DELAY 50`, `TAP_CODE_DELAY 10` 적용으로 무선 전송 시 텍스트 누락 방지
* **Expanded Macro Storage**: 6개 레이어(`DYNAMIC_KEYMAP_LAYER_COUNT 6`), 키 오버라이드 해제로 매크로 공간 **~446 바이트로 2.5배 확장**
* **Combos & Tap Dance**: 4개씩 온전히 유지 (`VIAL_COMBO_ENTRIES 4`, `VIAL_TAP_DANCE_ENTRIES 4`)
* **Lightweight RGB**: 단색(Solid) 및 숨쉬기(Breathing) 모드로 MCU 부하 경감 및 안정성 확보

---

## 🚀 Flashing (펌웨어 플래싱 방법)

1. `Esc`(또는 `Tab`+`Q`)를 누른 상태에서 USB 케이블을 컴퓨터에 연결합니다.
2. PC에 외장 USB 드라이브(`Atmel Corp. LUFA Mass Storage Demo`)가 인식됩니다.
3. 빌드된 `geonix40_geonix40_vial.bin` 파일을 해당 드라이브로 복사(드래그 앤 드롭)하면 자동으로 플래싱 후 재부팅됩니다.

---

## 🌐 Configurator (키매핑)

* **VIAL Web**: [https://vial.rocks/](https://vial.rocks/)
* VIA 호환 프로토콜 및 실시간 키맵, 콤보, 탭댄스, 매크로 지원
