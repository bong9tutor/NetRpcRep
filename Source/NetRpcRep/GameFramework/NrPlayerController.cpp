// Fill out your copyright notice in the Description page of Project Settings.

#include "NrPlayerController.h"

#include "NrGameMode.h"
#include "NrGameState.h"
#include "UI/NrChatWidget.h"

ANrPlayerController::ANrPlayerController()
{
    static ConstructorHelpers::FClassFinder<UNrChatWidget> ChatWidgetClassRef(TEXT("/Game/UI/WBP_Chat"));
    if (ChatWidgetClassRef.Succeeded())
    {
        ChatWidgetClass = ChatWidgetClassRef.Class;
    }
}

void ANrPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!IsLocalController())
        return;

    if (ChatWidgetClass)
    {
        CachedChatWidget = CreateWidget<UNrChatWidget>(this, ChatWidgetClass);
        if (CachedChatWidget)
        {
            CachedChatWidget->AddToViewport(0);
        }
    }

    GetWorldTimerManager().SetTimer(ServerTimePollHandle, this, &ANrPlayerController::PollServerTime, 1.f, true, 0.f);
}

bool ANrPlayerController::Server_ApplyDamage_Validate(const int32 Damage)
{
    return true;
}

void ANrPlayerController::Server_ApplyDamage_Implementation(const int32 Damage)
{
    if (const ANrGameMode* GM = GetWorld()->GetAuthGameMode<ANrGameMode>())
    {
        GM->ApplyDamageToAllPlayers(this, Damage);
    }
}

void ANrPlayerController::Server_SubmitMessage_Implementation(const FString& Message)
{
    if (const ANrGameMode* GM = GetWorld()->GetAuthGameMode<ANrGameMode>())
    {
        GM->SubmitMessage(this, Message);
    }
}

void ANrPlayerController::Client_ReceiveMessage_Implementation(const FString& Message)
{
    AddChatMessage(Message);
}

void ANrPlayerController::ReceivedCurrentHealth(const int32 CurHealth) const
{
    if (!IsLocalController())
        return;

    if (CachedChatWidget)
    {
        CachedChatWidget->UpdateHealth(CurHealth);
    }
}

void ANrPlayerController::AddChatMessage(const FString& Message) const
{
    if (!IsLocalController())
        return;

    if (CachedChatWidget)
    {
        CachedChatWidget->AddMessage(Message);
    }
}

void ANrPlayerController::PollServerTime() const
{
    const ANrGameState* GS = GetWorld()->GetGameState<ANrGameState>();
    if (!GS || !CachedChatWidget)
        return;

    CachedChatWidget->UpdateServerTime(GS->GetServerTime());
}
