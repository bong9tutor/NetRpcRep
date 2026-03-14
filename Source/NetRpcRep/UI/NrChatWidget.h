// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NrChatWidget.generated.h"

class UEditableTextBox;
class UScrollBox;
class UTextBlock;

/**
 * [UMG 채팅 UI] 채팅 입력/출력 및 플레이어 상태 표시
 *
 * 주요 기능:
 * - AddMessage           : 수신 메시지를 ScrollBox에 TextBlock으로 추가
 * - UpdateHealth         : 현재 체력을 CurrentHealthTextBlock에 갱신
 * - UpdateServerTime     : 서버 시간을 ServerTimeTextBlock에 갱신
 * - OnInputTextCommitted : 입력 확정 시 "공격" 키워드면 Server_ApplyDamage,
 *                          그 외 텍스트는 Server_SubmitMessage 호출
 *
 * WBP 바인딩 위젯:
 * - ScrollBox            : 채팅 메시지 목록
 * - InputTextBox         : 채팅 메시지 입력창
 * - CurrentHealthTextBlock: 현재 체력 표시
 * - ServerTimeTextBlock  : 서버 경과 시간 표시
 */
UCLASS()
class NETRPCREP_API UNrChatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

public:
    void UpdateHealth(const int32 Health) const;
    void UpdateServerTime(const float Time) const;
    void AddMessage(const FString& Message);

protected:
    UFUNCTION()
    void OnInputTextCommitted(const FText& Text, ETextCommit::Type CommitType);

protected:
    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UScrollBox> ScrollBox;

    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UEditableTextBox> InputTextBox;

    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UTextBlock> CurrentHealthTextBlock;

    UPROPERTY(meta=(BindWidget))
    TObjectPtr<UTextBlock> ServerTimeTextBlock;
};
