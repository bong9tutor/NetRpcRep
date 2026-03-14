// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NrGameMode.generated.h"

/**
 * [서버 전용] 게임 규칙 및 권위 처리 담당
 *
 * 주요 기능:
 * - ApplyDamageToAllPlayers : 모든 플레이어에게 데미지 적용 (PlayerState.Health 감소)
 * - SubmitMessage           : 클라이언트로부터 메시지 수신 후 라우팅 결정
 * - BroadcastMessage        : GameState를 통해 모든 클라이언트로 메시지 Multicast
 * - UpdateServerTime        : 타이머로 GameState.ServerTime 주기적 갱신
 */
UCLASS()
class NETRPCREP_API ANrGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    ANrGameMode();

public:
    void ApplyDamageToAllPlayers(const APlayerController* Attacker, const int32 Damage) const;
    void SubmitMessage(APlayerController* PC, const FString& Message) const;
    void BroadcastMessage(const FString& Message, const APlayerController* Sender) const;
};
