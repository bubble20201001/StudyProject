// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StudyProjectGameModeBase.generated.h"

/*
 �ӽ÷� ���⿡�� ���� ��ȣ�ۿ���
 �÷��̾� ��Ʈ�ѷ� ���� �� ���� ���� �ű��
 */

UENUM(BlueprintType)
enum class EGameState : uint8
{
	GameStart,
	GamyPlay,
	GamePause,
	GameOver,
};

UCLASS()
class STUDYPROJECT_API AStudyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	AStudyProjectGameModeBase();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> HUDWidgetClass; // TSubclassOf�� UUserWidget�� ���� �� �ֵ��� Ÿ���� �����ϴ� ��

	UUserWidget* CurrentWidget;
public:
	void ChangeUI();

private:
	TSubclassOf<UUserWidget>uiInventoryBPClass;
	UUserWidget* uiInventoryWidget;
};
