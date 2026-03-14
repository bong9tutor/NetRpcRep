// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NrPlayerController.generated.h"

class UNrChatWidget;

/**
 * [클라이언트↔서버 RPC 허브] 입력 처리 및 UI 연결 담당
 *
 * 주요 기능:
 * - Server_ApplyDamage  : [Server RPC] 클라이언트 요청 → GameMode에 데미지 처리 위임
 * - Server_SubmitMessage: [Server RPC] 클라이언트 채팅 입력 → GameMode에 메시지 라우팅 위임
 * - Client_ReceiveMessage: [Client RPC] 서버로부터 메시지 수신 → 채팅 위젯에 출력
 * - PollServerTime      : 타이머로 GameState.ServerTime을 주기적으로 읽어 위젯 갱신
 * - BeginPlay           : ChatWidget(WBP_Chat) 생성 및 뷰포트에 추가
 */
UCLASS()
class NETRPCREP_API ANrPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ANrPlayerController();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_ApplyDamage(const int32 Damage);

    UFUNCTION(Server, Reliable)
    void Server_SubmitMessage(const FString& Message);

    UFUNCTION(Client, Reliable)
    void Client_ReceiveMessage(const FString& Message);

    void ReceivedCurrentHealth(const int32 CurHealth) const;
    void AddChatMessage(const FString& Message) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category=UI)
    TSubclassOf<UNrChatWidget> ChatWidgetClass;

private:
    void PollServerTime() const;

    UPROPERTY()
    TObjectPtr<UNrChatWidget> CachedChatWidget;

    FTimerHandle ServerTimePollHandle;
    int32 MaxDamage = 10;
};
