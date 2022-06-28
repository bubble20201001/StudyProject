// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartMenu_GameMode.generated.h"

/*
 메인 메뉴용 게임모드 새로 제작
 */
UCLASS()
class STUDYPROJECT_API AStartMenu_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AStartMenu_GameMode();

	void BeginPlay() override;
};
