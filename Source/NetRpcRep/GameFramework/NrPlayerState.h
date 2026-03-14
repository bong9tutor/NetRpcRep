// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NrPlayerState.generated.h"

/**
 * [서버→소유 클라이언트 복제] 플레이어 개인 상태 관리
 *
 * 주요 기능:
 * - Health       : 체력 값(초기 100). ReplicatedUsing=OnRep_Health로 변경 시 UI 자동 갱신
 * - OnRep_Health : Health 복제 콜백. PlayerController를 통해 채팅 위젯 체력 표시 업데이트
 */
UCLASS()
class NETRPCREP_API ANrPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void BeginPlay() override;

public:
    FORCEINLINE int32 GetHealth() const { return Health; }
    FORCEINLINE void  SetHealth(const int32 NewHealth) { Health = NewHealth; }

protected:
    UFUNCTION()
    void OnRep_Health(int32 OldHealth);

    UPROPERTY(Transient, ReplicatedUsing=OnRep_Health)
    int32 Health = 100;
};
