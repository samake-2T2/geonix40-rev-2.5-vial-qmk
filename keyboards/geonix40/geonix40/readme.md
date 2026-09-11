# GEONIX40 (Rev.2.5)

GEONIX40 (Rev.2.5) Tri-mode (USB / Bluetooth / 2.4G) 40% Mechanical Keyboard firmware for QMK / VIAL.  
(GEONIX40 Rev.2.5 삼중 모드 유무선 40% 기계식 키보드 QMK / VIAL 펌웨어)

* **Hardware Supported (지원 하드웨어)**: GEONIX40 Rev.2.5 PCB with Eastsoft ES32FS026 MCU (FS026 + 91680)
* **Connectivity (연결 방식)**: USB-C Wired, Bluetooth 5.0 (3 Channels), 2.4GHz RF
* **Lighting (조명)**: Per-key RGB Matrix Backlight & Logo / Side LEDs (WS2812)
* **Configurator (키매핑 지원)**: VIAL (Web & Desktop App) & VIA compatible

---

## Build Examples (빌드 예제)

### VIAL Keymap (VIAL 키맵 빌드)
```bash
make geonix40/geonix40:vial
```

### Default Keymap (기본 키맵 빌드)
```bash
make geonix40/geonix40:default
```

---

## Bootloader Mode (부트로더 모드 진입 방법)

Enter the bootloader in 2 ways (부트로더 모드로 진입하는 2가지 방법):

1. **Bootmagic Reset (부트매직 리셋)**:  
   Hold down the top-left key (Esc / Tab) while plugging in the USB cable.  
   (USB 케이블을 연결하는 동안 매트릭스 좌측 상단 키를 누르고 있습니다.)

2. **Physical Reset Button (물리 리셋 버튼)**:  
   Briefly press the reset button on the back of the PCB.  
   (PCB 후면의 리셋 버튼을 누릅니다.)
