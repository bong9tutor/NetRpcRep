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
