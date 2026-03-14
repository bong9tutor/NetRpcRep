// Fill out your copyright notice in the Description page of Project Settings.

#include "NrChatWidget.h"
#include "GameFramework/NrPlayerController.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UNrChatWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (InputTextBox)
        InputTextBox->OnTextCommitted.AddDynamic(this, &UNrChatWidget::OnInputTextCommitted);
}

void UNrChatWidget::NativeDestruct()
{
    if (InputTextBox)
        InputTextBox->OnTextCommitted.RemoveAll(this);

    Super::NativeDestruct();
}

void UNrChatWidget::UpdateHealth(const int32 Health) const
{
    if (!CurrentHealthTextBlock)
        return;

    CurrentHealthTextBlock->SetText(FText::AsNumber(Health));
}

void UNrChatWidget::UpdateServerTime(const float Time) const
{
    if (!ServerTimeTextBlock)
        return;

    ServerTimeTextBlock->SetText(FText::AsNumber(FMath::FloorToInt(Time)));
}

void UNrChatWidget::AddMessage(const FString& Message)
{
    if (!ScrollBox)
        return;

    UTextBlock* TextBlock = NewObject<UTextBlock>(this);
    TextBlock->SetText(FText::FromString(Message));
    ScrollBox->AddChild(TextBlock);
    ScrollBox->ScrollToEnd();
}

void UNrChatWidget::OnInputTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
    if (CommitType != ETextCommit::OnEnter)
        return;

    const FString InputStr = Text.ToString();
    if (InputStr.IsEmpty())
        return;

    ANrPlayerController* PC = Cast<ANrPlayerController>(GetOwningPlayer());
    if (!PC)
        return;

    if (InputStr.Equals(TEXT("공격")))
    {
        // todo: 서버에 데미지 이벤트 호출
        AddMessage(TEXT("[시스템] 모든 플레이어를 공격(10) 시작"));
    }
    else
    {
        // todo: 서버에 메시지 송신 이벤트 호출
    }

    InputTextBox->SetText(FText::GetEmpty());

    FTimerDelegate NextTickDelegate;
    NextTickDelegate.BindWeakLambda(this, [this]()
    {
        if (IsValid(InputTextBox))
            InputTextBox->SetKeyboardFocus();
    });
    GetWorld()->GetTimerManager().SetTimerForNextTick(NextTickDelegate);
}
