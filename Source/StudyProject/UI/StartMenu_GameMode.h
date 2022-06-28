// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartMenu_GameMode.generated.h"

/*
 ���� �޴��� ���Ӹ�� ���� ����
 */
UCLASS()
class STUDYPROJECT_API AStartMenu_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AStartMenu_GameMode();

	void BeginPlay() override;
};