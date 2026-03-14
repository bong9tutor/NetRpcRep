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
        PC->ReceivedCurrentHealth(Health);
    }
}

void ANrPlayerState::OnRep_Health(int32 OldHealth)
{
    if (const ANrPlayerController* PC = Cast<ANrPlayerController>(GetOwner()))
    {
        PC->ReceivedCurrentHealth(Health);
    }
}
