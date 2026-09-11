# Chosfox Geonix Rev.2.5 — VIAL / QMK Firmware

A vendor-modified QMK/VIAL firmware for the **Chosfox x Masro Geonix Rev.2.5** (tri-mode: USB / BLE 5.0 / 2.4GHz RF), a 40% ortholinear mechanical keyboard with 47 keys.

(Chosfox x Masro **Geonix Rev.2.5** 삼중 모드 유무선 40% 직교 배열 47키 기계식 키보드를 위한 QMK / VIAL 펌웨어입니다.)

---

## 📌 Origin and Architecture (기반 아키텍처)

| 항목 (Property) | 내용 (Value) |
| :--- | :--- |
| **Keyboard Model** | Chosfox Geonix Rev.2.5 (Designed by Masro, Produced by Chosfox) |
| **Main MCU** | Eastsoft (Essemi) **ES32FS026** (ARM Cortex-M0 @ 48MHz~72MHz) |
| **Wireless Module** | **91680** (YC91680 / RDM026), SPI communication with MCU |
| **QMK Base** | QMK 0.22.x / ChibiOS customized vendor fork |
| **Configurator** | **VIAL** (Native Web/Desktop) & VIA Protocol compatible |
| **Firmware Build** | V0106 (Enhanced Macro Delay 50ms, 6-Layer Layout, 2.5x Macro EEPROM) |

이 키보드는 메인라인 QMK/ChibiOS에서 공식 지원하지 않는 **Eastsoft ES32FS026** MCU를 사용합니다. 제조사(RDMCTMZT / Finalkey, LiWenLiu)에서 작성한 커스텀 ChibiOS HAL 포트(`chibios-contrib`)와 무선 통신/배터리/LED/부트로더를 제어하는 독점 바이너리 라이브러리(`lib/rdr_lib/librdrcommon.a`)를 기반으로 구동됩니다.

---

## 🔬 Hardware Specifications (하드웨어 상세 명세)

| 하드웨어 구성 요소 | 상세 사양 (Specifications) |
| :--- | :--- |
| **Microcontroller (MCU)** | Eastsoft (上海东软载波) **ES32FS026**<br>• Core: 32-bit ARM Cortex-M0 RISC<br>• Clock: 48 MHz (최대 72 MHz PLL 지원)<br>• Operating Voltage: 3.3V |
| **Memory (메모리)** | • **Flash (ROM)**: **128 KB** (펌웨어 바이너리 공간, 현재 약 77KB 사용)<br>• **SRAM (RAM)**: **16 KB** (스캔, 키 버퍼, LED 프레임 버퍼)<br>• **Emulated EEPROM**: 4 KiB Flash 중 **1,152 바이트** 할당 |
| **Wireless Connectivity** | **91680 (YC91680 / RDM026) Tri-Mode 3.0 SoC**<br>• **Bluetooth 5.0 LE**: 3개 프로필 멀티페어링 (`BLE1`, `BLE2`, `BLE3`)<br>• **2.4GHz Wireless RF**: 전용 초저지연 USB 동글 연결<br>• **Interface**: 고속 SPI 통신 (MCU ↔ 91680) |
| **Wired Connection** | USB 2.0 Full-Speed (12 Mbps), Type-C 포트 |
| **USB VID / PID** | `0x36B0` / `0x313B` |
| **Key Matrix (매트릭스)** | **4 Rows × 12 Columns**, `ROW2COL` 다이오드 방향 (총 47키 직교 배열)<br>• **Row Pins (4개)**: `B0`, `B4`, `B5`, `B6`<br>• **Col Pins (12개)**: `D15`, `D14`, `C15`, `C14`, `C13`, `D3`, `D2`, `C12`, `C11`, `C10`, `A14`, `C9` |
| **Layout (레이아웃)** | 40% Ortholinear (4x12 그리드 기반, 3번 행 중앙 2U 스페이스바 지원) |
| **Lighting (RGB LED)** | **총 76개 WS2812 RGB LED** (하드웨어 PWM + DMA 구동)<br>• 스위치 백라이트: 47개 개별 키 RGB<br>• 사이드 & 로고 엠비언트: 29개 RGB<br>• 최적화 모드: Solid Color (단색) 및 Breathing (숨쉬기) |
| **Power & Battery** | 리튬 폴리머(LiPo) 배터리 충전 지원, 12-bit ADC 기반 배터리 모니터링 (Pin `A13`), 2단계 자동 절전(Sleep / Deep Sleep) 지원 |

---

## 💾 Memory Architecture & EEPROM Limits (메모리 구조 및 주의사항)

### 1. Flash 기반 가상 EEPROM 구조
ES32FS026 칩에는 물리적 EEPROM이 없으므로 플래시 메모리의 끝부분 **4 KiB (`0x1F000` ~ `0x1FFFF`)** 영역을 가상 EEPROM으로 에뮬레이션합니다:

* **Compacted Data Area (기본 데이터 영역)**: 실제 키맵 및 설정값이 저장되는 영역 (최대 **1,152 바이트**)
* **Write Log Buffer (쓰기 로그 버퍼, 약 2.9 KiB)**: 플래시 수명(P/E 사이클)을 보호하기 위한 웨어 레벨링(Wear-Leveling) 버퍼. 키맵 변경 시 플래시를 매번 지우지 않고 변경 이력을 누적 기록합니다.

### ⚠️ 중요: 1,152 바이트 HardFault 한계
벤더 바이너리 블롭(`librdrcommon.a`) 내부의 EEPROM 캐시 버퍼 크기가 **1,152 바이트**로 고정되어 있습니다. `EEPROM_SIZE`를 1,152바이트 이상으로 늘리거나 무리하게 레이어를 추가하면 부팅 시 **HardFault 크래시**가 발생합니다.

### 2. V0106 매크로 공간 최적화 (2.5배 확장)
1,152 바이트의 협소한 공간을 효율적으로 사용하기 위해 불필요한 레이어와 기능을 최적화했습니다:

* **레이어 수 6개로 조정 (`DYNAMIC_KEYMAP_LAYER_COUNT 6`)**: 8개 레이어 대비 **188 바이트 절약**
* **키 오버라이드 비활성화 (`KEY_OVERRIDE_ENABLE = no`)**: 미사용 기능 해제로 **80 바이트 절약**
* **콤보(4개) 및 탭댄스(4개) 유지**: 핵심 커스텀 기능은 유지
* **결과**: 순수 매크로 할당 공간이 기존 약 178 바이트에서 **약 446 바이트(약 2.5배)**로 대폭 확장되었습니다.

---

## 📦 Proprietary Binary Blob (`lib/rdr_lib/`)

벤더 라이브러리(`librdrcommon.a`, `rdr_common.h`)는 다음과 같은 핵심 하드웨어 제어를 비공개 바이너리 형태로 처리합니다:

1. **무선 통신 & HID 라우팅**: `es_send_keyboard()`, `es_send_nkro()`, `es_send_mouse()` 등 유선/무선 모드에 따른 패킷 분기 및 SPI 전송
2. **배터리 관리**: ADC 전압 측정, 충전 상태 감지, 저전압 컷오프
3. **RGB LED 제어**: PWM + DMA 기반의 고속 WS2812 신호 출력
4. **부트로더 점프**: `bootloader_jump()` 호출 시 ROM 부트로더 주소(`0x1FFFC800`)로 안전하게 점프

---

## ⌨️ Custom Keycodes (전용 특수 키코드)

`lib/rdr_lib/rdr_common.h`에 정의된 지오닉스 전용 키코드 목록입니다:

| 키코드 (Keycode) | 단축 이름 (Alias) | 기능 설명 (Description) |
| :--- | :--- | :--- |
| `QMK_KB_MODE_USB` | `MD_USB` | USB 유선 모드로 전환 |
| `QMK_KB_MODE_BLE1` | `MD_BLE1` | 블루투스 슬롯 1로 전환 |
| `QMK_KB_MODE_BLE2` | `MD_BLE2` | 블루투스 슬롯 2로 전환 |
| `QMK_KB_MODE_BLE3` | `MD_BLE3` | 블루투스 슬롯 3로 전환 |
| `QMK_KB_MODE_2P4G` | `MD_24G` | 2.4GHz 무선 동글 모드로 전환 |
| `QMK_KB_BLE1_PAIR` | — | 블루투스 슬롯 1 페어링 모드 진입 |
| `QMK_KB_BLE2_PAIR` | — | 블루투스 슬롯 2 페어링 모드 진입 |
| `QMK_KB_BLE3_PAIR` | — | 블루투스 슬롯 3 페어링 모드 진입 |
| `QMK_KB_2P4G_PAIR` | — | 2.4GHz 무선 리시버 페어링 모드 진입 |
| `QMK_BATT_NUM` | `QK_BAT` | 현재 배터리 잔량을 숫자/LED로 표시 |
| `RGB_RTOG` | — | 사이드 / 로고 엠비언트 LED 효과 전환 |
| `U_EE_CLR` | — | 무선 페어링 및 키보드 하드웨어 설정 초기화 |
| `USER_CHANGE` | `KC_UC` | Mac 모드 / Windows 모드 레이아웃 전환 |
| `QMK_WIN_LOCK` | `QK_WLO` | Windows 키 잠금(Win Lock) 토글 |
| `QMK_KB_SIX_N_CH` | `SIX_N` | 6KRO / NKRO 전환 |

---

## 🚀 Flashing Guide (펌웨어 플래싱 방법)

키보드에는 ROM 부트로더(`0x1FFFC800`)가 내장되어 있어 전용 프로그램 없이도 USB 드라이브 복사 방식으로 가장 쉽고 안전하게 플래싱할 수 있습니다.

### 방법 1. 가상 USB 드라이브 복사 (가장 권장)
1. USB 케이블을 분리합니다.
2. 키보드의 **좌상단 키(`Tab` + `Q` 또는 `Esc`)**를 누른 상태에서 USB 케이블을 PC에 연결합니다. (또는 기판 후면 리셋 버튼 클릭)
3. PC의 '내 PC'에 **외장 USB 드라이브**(`Atmel Corp. LUFA Mass Storage Demo`)가 자동으로 인식되어 폴더가 열립니다.
4. 빌드된 **`geonix40_geonix40_vial.bin`** 파일을 해당 드라이브 폴더로 **드래그 앤 드롭(복사)**합니다.
5. 파일 복사가 완료되면 드라이브가 자동으로 닫히고 키보드가 재부팅되며 즉시 새 펌웨어로 동작합니다.

### 방법 2. QMK Toolbox 사용
1. **`QMK Toolbox`** 실행
2. `Open`을 눌러 `geonix40_geonix40_vial.bin` 또는 `.hex` 파일 선택
3. 키보드를 부트로더 모드로 진입시킨 후 **`Flash`** 버튼 클릭

---

## 🌐 Web Configurator (VIAL 설정)

* **VIAL Web 주소**: [https://vial.rocks/](https://vial.rocks/)
* 별도 프로그램 설치 없이 크롬/엣지 웹 브라우저에서 키보드를 즉시 연결하여 키 매핑, 콤보, 탭댄스, 매크로를 직관적인 GUI로 실시간 수정할 수 있습니다.
* 무선 모드에서 텍스트 입력 시 잘림 현상을 방지하기 위해 기본 지연 시간 50ms(`DYNAMIC_KEYMAP_MACRO_DELAY 50`)가 내장되어 있습니다.

---

## 🛠️ Compilation (로컬 빌드 방법)

```bash
# VIAL 키맵 컴파일 (권장)
make geonix40/geonix40:vial

# 기본(Default) QMK 키맵 컴파일
make geonix40/geonix40:default
```
