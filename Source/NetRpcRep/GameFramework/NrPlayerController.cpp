// Fill out your copyright notice in the Description page of Project Settings.

#include "NrPlayerController.h"

#include "NrGameMode.h"
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
}

bool ANrPlayerController::Server_ApplyDamage_Validate(const int32 Damage)
{
    return true;
}

void ANrPlayerController::Server_ApplyDamage_Implementation(const int32 Damage)
{
    if (const ANrGameMode* GM = GetWorld()->GetAuthGameMode<ANrGameMode>())
    {
        // todo: 서버에 ApplyDamage를 호출한 플레이어를 제외한 다른 플레이더를에게 데미지를 주는 함수 호출
    }
}

void ANrPlayerController::Server_SubmitMessage_Implementation(const FString& Message)
{
    if (const ANrGameMode* GM = GetWorld()->GetAuthGameMode<ANrGameMode>())
    {
        // todo: 서버에 메세지를 Submit 하는 함수 호출
    }
}
