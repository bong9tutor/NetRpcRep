# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 프로젝트 개요

Unreal Engine 5.6 C++ 프로젝트. 멀티플레이어 네트워킹(RPC, 데이터 복제)을 학습 목적으로 시연하는 프로젝트.

## 빌드 및 실행

- **Visual Studio 2022**에서 `NetRpcRep.sln` 열기
- 우클릭 `NetRpcRep.uproject` → "Generate Visual Studio project files" 후 빌드
- 기본 맵: `/Game/Maps/L_Game`
- 모듈 의존성: Core, CoreUObject, Engine, InputCore, EnhancedInput, UMG, SlateCore

## 아키텍처

### 네트워크 구조 (서버 권위 모델)

```
클라이언트 입력 (NrChatWidget)
    ↓
ANrPlayerController (서버 RPC 호출)
    ↓
ANrGameMode (서버 권위 처리)
    ↓
ANrPlayerState (Health 복제) + ANrGameState (Multicast 메시지)
    ↓
모든 클라이언트 수신
```

### 핵심 클래스 (`Source/NetRpcRep/`)

| 클래스 | 역할 |
|---|---|
| `ANrGameMode` | 서버 전용. 데미지 적용(`ApplyDamageToAllPlayers`) 및 메시지 라우팅(`SubmitMessage`, `BroadcastMessage`) |
| `ANrGameState` | `Multicast_BroadcastMessage` RPC로 모든 클라이언트에 메시지 전송 |
| `ANrPlayerState` | `Health`(복제 변수, `OnRep_Health` 콜백) 관리. 초기값 100 |
| `ANrPlayerController` | 서버 RPC(`Server_ApplyDamage`, `Server_SubmitMessage`), 클라이언트 RPC(`Client_ReceiveMessage`), UI 위젯 생성 |
| `UNrChatWidget` | UMG 채팅 UI. "공격" 입력 시 `Server_ApplyDamage` 호출, 일반 텍스트는 `Server_SubmitMessage` 호출 |

### UI

- 위젯 블루프린트: `/Game/UI/WBP_Chat`
- 컴포넌트: ScrollBox(메시지 목록), EditableTextBox(입력), TextBlock(체력 표시)

## 개발 규칙

### 구현 원칙
- SOLID 원칙, Clean Architecture 적용
- 단순성 우선: 가장 단순하게 솔루션을 구성

### 코드 품질
- 중복 방지 (DRY 원칙)
- 테스트 외에는 모의 데이터 사용 금지
- 출력은 토큰 최소화 방향으로 최적화

### 리팩토링
- 계획을 설명하고 허락을 받은 후 진행
- 기능 변경 없이 구조 개선이 목표

### 디버깅
- 원인 / 해결책을 설명하고 허락 후 진행
- 원인 불분명 시 `UE_LOG`로 상세 로그 추가

### 언어
- 기본 언어는 한글
- 기술 용어 / 라이브러리명은 원문 유지
- 주석은 한국어로 작성

### 금지 사항
- 민감 파일 읽기 금지
- 비동기 코드를 동기처럼 변경 금지
- 동작을 임의로 단축하거나 생략 금지
- 언리얼 엔진 내 소스 수정 금지

### 언리얼 엔진 코드 규칙
- `TObjectPtr`, 포인터 변수는 `UPROPERTY` 매크로로 선언
- CPP 파일에서 Self Header를 가장 먼저 Include
- 함수: PascalCase (명사+동사)
- 변수: Prefix + PascalCase (`bIsAlive`, `PlayerScore`)
- `BlueprintCallable` 함수는 `Category` 명시
