# GEONIX40 Firmware Changelog (펌웨어 변경 이력)

---

### [V0106] - 2026-09-11
- **Hardware / Firmware Info (기본 정보)**: RDM026+91680 - GEONIX40 (Rev.2.5) - VIAL - Tri-Mode 3.0 - Mechanical Keyboard - V0106
- **Backlight (백라이트)**: WS2812 (Solid Color & Breathing)
- **Logo LED (로고 LED)**: WS2812 (Solid Color & Breathing)
- **VID / PID**: `0x36B0 / 0x313B`
- **Changes (변경 내역)**:
  - Applied 50ms macro character delay (`DYNAMIC_KEYMAP_MACRO_DELAY 50`) to prevent text truncation in wireless (BLE / 2.4G) mode (무선 모드 텍스트 매크로 잘림 방지 50ms 지연 시간 적용)
  - Optimized layer count from 8 to 6 (`DYNAMIC_KEYMAP_LAYER_COUNT 6`) to expand macro EEPROM capacity by ~2.5x (레이어 6개 최적화를 통한 매크로 가용 용량 2.5배 대폭 확장)
  - Disabled unused key overrides (`KEY_OVERRIDE_ENABLE = no`) while retaining Combos (4) and Tap Dance (4), freeing additional EEPROM space for macros (키 오버라이드 비활성화, 콤보 및 탭댄스는 온전히 유지하여 매크로 메모리 환원)
  - Streamlined RGB Matrix animations to Solid and Breathing modes to reduce MCU load and improve wireless communication stability (스위치 RGB 애니메이션을 솔리드/숨쉬기로 경량화하여 무선 통신 안정성 향상)

---

### [V0105] - 2026-05-18
- **Hardware / Firmware Info (기본 정보)**: RDM026+91680 - Geonix41 - VIAL - Tri-Mode 3.0 - Mechanical Keyboard - CSD939 - V0105
- **Backlight (백라이트)**: WS2812
- **Logo LED (로고 LED)**: WS2812
- **VID / PID**: `0x36B0 / 0x313F`
- **Previous Version (이전 버전)**: V0104 (CS15E0)
- **Checksum (체크섬)**: D939 (0x0105)
- **Notes (참고 사항)**: Requires pairing with new RF receiver (새로운 RF 및 수신기 동글 페어링 필요)
- **Changes (변경 내역)**:
  - Fixed VIAL layout JSON file (VIAL 레이아웃 JSON 파일 수정)

---

### [V0104] - 2026-05-16
- **Hardware / Firmware Info (기본 정보)**: RDM026+91680 - Geonix41 - VIAL - Tri-Mode 3.0 - Mechanical Keyboard - CS15E0 - V0104
- **Backlight (백라이트)**: WS2812
- **Logo LED (로고 LED)**: WS2812
- **VID / PID**: `0x36B0 / 0x313F`
- **Previous Version (이전 버전)**: V0103 (CS0D65)
- **Checksum (체크섬)**: 15E0 (0x0104)
- **Notes (참고 사항)**: Requires pairing with new RF receiver (새로운 RF 및 수신기 동글 페어링 필요)
- **Changes (변경 내역)**:
  - Added VIAL configurator support (VIAL 웹/앱 키매핑 지원 적용)

---

### [V0103] - 2026-03-24
- **Hardware / Firmware Info (기본 정보)**: RDM026+91680 - Geonix41 - Tri-Mode 3.0 - Mechanical Keyboard - CS0D65 - V0103
- **Backlight (백라이트)**: WS2812
- **Logo LED (로고 LED)**: WS2812
- **VID / PID**: `0x36B0 / 0x313F`
- **Previous Version (이전 버전)**: V0102 (CS6A6D)
- **Checksum (체크섬)**: 0D65 (0x0103)
- **Notes (참고 사항)**: Requires pairing with new RF receiver (새로운 RF 및 수신기 동글 페어링 필요)
- **Changes (변경 내역)**:
  - `FN + ENTER`: Toggle ambient/side LED effects (엠비언트/사이드 LED 조명 효과 전환)

---

### [V0102] - 2026-03-16
- **Hardware / Firmware Info (기본 정보)**: RDM026+91680 - Geonix41 - Tri-Mode 3.0 - Mechanical Keyboard - CS6A6D - V0102
- **Backlight (백라이트)**: WS2812
- **Logo LED (로고 LED)**: WS2812
- **VID / PID**: `0x36B0 / 0x313F`
- **Previous Version (이전 버전)**: V0101 (CSF0ED)
- **Checksum (체크섬)**: 6A6D (0x0102)
- **Notes (참고 사항)**: Requires pairing with new RF receiver (새로운 RF 및 수신기 동글 페어링 필요)
- **Changes (변경 내역)**:
  - Ambient/side LEDs separated into independent lighting effect, no longer linked directly to key backlights (엠비언트/사이드 LED 효과를 키 백라이트와 분리하여 독립 제어되도록 변경)
  - `FN + ENTER`: Turn off ambient LED effects (엠비언트 LED 효과 끄기)

---

### [V0101] - 2026-03-04
- **Hardware / Firmware Info (기본 정보)**: RDM026+91680 - Geonix41 - Tri-Mode 3.0 - Mechanical Keyboard - CSF0ED - V0101
- **Backlight (백라이트)**: WS2812
- **Logo LED (로고 LED)**: WS2812
- **VID / PID**: `0x36B0 / 0x313F`
- **Previous Version (이전 버전)**: V0100 (CS6CD9)
- **Checksum (체크섬)**: F0ED (0x0101)
- **Notes (참고 사항)**: Requires pairing with new RF receiver (새로운 RF 및 수신기 동글 페어링 필요)
- **Changes (변경 내역)**:
  - Changed Bluetooth device name to: `GEONIX REV.2.5 1U` (블루투스 기기명 변경)
  - Changed Wired USB device name to: `GEONIX REV.2.5 1U` (유선 USB 기기명 변경)
  - Updated OS Mode indicator LED behavior (Win/Mac 시스템 모드 표시등 위치 변경):
    - `FN + U`: Switch to Windows mode (U key illuminates white / U키 흰색 점등)
    - `FN + Y`: Switch to macOS mode (Y key illuminates white / Y키 흰색 점등)
    - When holding `FN`, either `U` or `Y` key stays lit in solid white to indicate current OS mode (FN 키를 누르고 있는 동안 U 또는 Y키가 흰색으로 켜져 현재 운영체제 모드 확인 가능)
  - Removed `FN + ENTER` lighting test mode (조명 테스트 모드 제거)
  - Synced 8 ambient LEDs with main switch backlights (8개 사이드 엠비언트 LED를 스위치 백라이트와 연동)
  - While charging, FN key lights up in red, then restores to default after 10 seconds (충전 시작 시 FN키가 빨간색으로 점등되며 10초 후 원래 상태로 복귀)

---

### [V0100] - 2026-01-08
- **Hardware / Firmware Info (기본 정보)**: FS026+91680 - Geonix41 - Tri-Mode 3.0 - Mechanical Keyboard - CS6CD9 - V0100
- **Backlight (백라이트)**: WS2812
- **Logo LED (로고 LED)**: WS2812
- **VID / PID**: `0x36B0 / 0x313F`
- **Checksum (체크섬)**: 6CD9 (0x0100)
- **Notes (참고 사항)**: Requires pairing with new RF receiver (새로운 RF 및 수신기 동글 페어링 필요)
- **Changes (변경 내역)**:
  - Initial project release (최초 프로젝트 릴리즈)