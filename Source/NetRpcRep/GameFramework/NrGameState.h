// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NrGameState.generated.h"

/**
 * [서버→모든 클라이언트 복제] 게임 전체 공유 상태 관리
 *
 * 주요 기능:
 * - ServerTime : 서버 경과 시간(초). Replicated로 모든 클라이언트에 동기화
 * - Multicast_BroadcastMessage (NrGameMode에서 호출): 채팅 메시지를 전체 클라이언트에 전송
 */
UCLASS()
class NETRPCREP_API ANrGameState : public AGameStateBase
{
	GENERATED_BODY()
};
