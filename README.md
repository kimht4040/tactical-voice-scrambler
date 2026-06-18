# Tactical Voice Scrambler
### 전술 음성 비화 및 C2 모니터링 시스템

---

## Project Overview

본 프로젝트는 방위산업 및 전술 통신 환경을 모사하여, 엣지 단말(Raspberry Pi)에서 수집된 음성 데이터를 실시간으로 암호화(Scrambling)하고 지휘통제소(C2 Server)로 안전하게 전송하는 임베디드 보안 통신 시스템입니다.

단순한 애플리케이션 레벨의 구현을 넘어, Yocto Project 기반의 커스텀 리눅스 환경 구축부터 ALSA 커널 드라이버 제어, 네트워크 프로토콜 특성을 고려한 망 분리 설계까지 — 하드웨어와 OS 전반을 아우르는 시스템 엔지니어링 역량을 증명하기 위해 기획되었습니다.

---

## Tech Stack & Hardware

| 구분 | 내용 |
|---|---|
| Edge Device | Raspberry Pi 4 Model B |
| Audio Codec | ReSpeaker 2-Mics Pi HAT (WM8960 I2S Codec) |
| OS & Kernel | Custom Embedded Linux (Yocto Project / Bitbake) |
| Languages | Modern C++ (Edge Node), Python 3 (C2 Server) |
| Network | UDP (Real-time Audio Streaming), TCP (Control & Telemetry) |

---

## System Architecture

본 시스템은 실시간성과 신뢰성을 동시에 확보하기 위해 제어망(Control Plane)과 데이터망(Data Plane)을 분리하여 설계되었습니다.

**1. Edge Node — Transmitter (C++)**

- `ALSA Driver` : WM8960 코덱 칩의 I2S 인터페이스를 통해 아날로그 마이크 입력을 캡처 (Zero-latency 버퍼링)
- `Crypto Engine` : CPU 오버헤드를 최소화한 경량화 주파수 변조 / 비트 역상 알고리즘 수행
- `UDP Socket` : 암호화된 오디오 스트림을 C2 서버로 지연 없이 전송
- `TCP Socket` : 단말기 헬스체크(CPU, 메모리 상태) 및 암호화 세션 키 교환

**2. C2 Server — Receiver (Python)**

- `Asyncio UDP/TCP` : 엣지 단말로부터 스트리밍 데이터 및 텔레메트리 동시 수신
- `Signal Processing` : 수신된 패킷의 암호를 복호화(Descrambling)하여 오디오 장치로 출력
- `Monitoring Dashboard` : 패킷 손실률(Packet Loss), 네트워크 지연(Latency), 단말 상태 시각화

---

## Repository Structure

```text
tactical-voice-scrambler/
├── edge_node/              # 라즈베리파이 C++ 소스코드
│   ├── src/                # ALSA 캡처, 암호화, 소켓 송신 로직
│   ├── include/             # 헤더 파일
│   └── CMakeLists.txt      # C++ 빌드 스크립트
├── c2_server/               # PC 관제 서버 Python 소스코드
│   ├── app.py                # 메인 비동기 서버 실행 파일
│   ├── crypto.py             # 복호화 알고리즘
│   └── dashboard_ui.py       # 상태 모니터링 GUI
└── meta-audio-crypto/        # Yocto 커스텀 레이어 (BSP 및 드라이버 설정)
    ├── recipes-kernel/       # ALSA 드라이버 포팅 레시피
    └── recipes-core/         # 커스텀 리눅스 이미지 빌드 설정
```
