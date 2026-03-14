// Fill out your copyright notice in the Description page of Project Settings.

#include "NrGameMode.h"

#include "NrGameState.h"
#include "NrPlayerController.h"
#include "NrPlayerState.h"

ANrGameMode::ANrGameMode()
{
    GameStateClass = ANrGameState::StaticClass();
    PlayerStateClass = ANrPlayerState::StaticClass();
    PlayerControllerClass = ANrPlayerController::StaticClass();
}

void ANrGameMode::ApplyDamageToAllPlayers(const APlayerController* Attacker, const int32 Damage) const
{
    const ANrGameState* GS = GetGameState<ANrGameState>();
    if (!GS) return;

    for (APlayerState* PlayerState : GS->PlayerArray)
    {
        if (Attacker == PlayerState->GetOwningController())
            continue;

        if (ANrPlayerState* PS = Cast<ANrPlayerState>(PlayerState))
        {
            PS->SetHealth(PS->GetHealth() - Damage);
        }
    }

    BroadcastMessage(FString::Printf(TEXT("[시스템] 누군가 당신을 공격(-%i) 합니다."), Damage), Attacker);
}

void ANrGameMode::SubmitMessage(APlayerController* PC, const FString& Message) const
{
    if (ANrPlayerController* BPC = Cast<ANrPlayerController>(PC))
    {
        // todo: 메시지를 보낸 플레이어에게 서버에서 메시지 수신 성공 메시지 보내기
    }

    BroadcastMessage(Message, PC);
}

void ANrGameMode::BroadcastMessage(const FString& Message, const APlayerController* Sender) const
{
    const ANrGameState* GS = GetGameState<ANrGameState>();
    if (!GS) return;

    for (const APlayerState* PS : GS->PlayerArray)
    {
        ANrPlayerController* PC = Cast<ANrPlayerController>(PS->GetOwningController());
        if (!PC || PC == Sender)
            continue;

        // todo: 현재 접속중인 플레이어들 중 메시지를 보낸 플레이어를 제외 하고 메시지 보내기
    }
}
