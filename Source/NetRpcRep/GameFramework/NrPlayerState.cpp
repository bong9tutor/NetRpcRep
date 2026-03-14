// Fill out your copyright notice in the Description page of Project Settings.

#include "NrPlayerState.h"

#include "NrPlayerController.h"
#include "Net/UnrealNetwork.h"

void ANrPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANrPlayerState, Health);
}

void ANrPlayerState::BeginPlay()
{
    Super::BeginPlay();

    if (const ANrPlayerController* PC = Cast<ANrPlayerController>(GetOwner()))
    {
        // todo: 플레이어의 UI Health 초기화를 위해 컨트롤러에 알림 (갱신)
    }
}

void ANrPlayerState::OnRep_Health(int32 OldHealth)
{
    if (const ANrPlayerController* PC = Cast<ANrPlayerController>(GetOwner()))
    {
        // todo: 플레이어의 UI Health 갱신을 위해 컨트롤러에 알림
    }
}
