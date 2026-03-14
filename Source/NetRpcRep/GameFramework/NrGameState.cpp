// Fill out your copyright notice in the Description page of Project Settings.

#include "NrGameState.h"

#include "Net/UnrealNetwork.h"

void ANrGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANrGameState, ServerTime);
}
