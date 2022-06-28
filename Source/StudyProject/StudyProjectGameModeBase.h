// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StudyProjectGameModeBase.generated.h"

/*
 임시로 여기에서 위젯 상호작용중
 플레이어 컨트롤러 만든 후 위젯 전부 옮기기
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
	TSubclassOf<UUserWidget> HUDWidgetClass; // TSubclassOf은 UUserWidget만 나올 수 있도록 타입을 제한하는 것

	UUserWidget* CurrentWidget;
public:
	void ChangeUI();

private:
	TSubclassOf<UUserWidget>uiInventoryBPClass;
	UUserWidget* uiInventoryWidget;
};
