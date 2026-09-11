# GEONIX40 (Rev.2.5) - VIAL Keymap

VIAL keymap for the GEONIX40 (Rev.2.5) Tri-mode mechanical keyboard.  
(GEONIX40 Rev.2.5 삼중 모드 기계식 키보드 전용 VIAL 키맵입니다.)

---

## Features (주요 기능)

* **VIAL Support (VIAL 지원)**: Real-time key remapping, macros, tap dance, and combo via [VIAL Web](https://vial.rocks) or VIAL desktop app.  
  (VIAL 웹 및 데스크탑 앱을 통한 실시간 키 매핑, 매크로, 탭댄스, 콤보 설정 지원)
* **Tri-Mode Wireless (삼중 무선 연결)**: USB-C 유선, 블루투스 5.0 (3개 채널), 2.4GHz 무선 지원
* **RGB Matrix & Side/Logo LED (조명 효과)**: 스위치 백라이트 및 사이드/로고 LED 독립 및 동기화 제어 지원

---

## Build (빌드 방법)

```bash
make geonix40/geonix40:vial
```

---

## Bootloader (부트로더 진입)

1. **Bootmagic Reset**: USB 케이블을 꽂는 동안 좌측 상단 키(Esc / Tab)를 길게 누릅니다.
2. **Physical Button**: PCB 후면의 물리 리셋 버튼을 누릅니다.
