// Fill out your copyright notice in the Description page of Project Settings.

#include "NrPlayerController.h"

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
