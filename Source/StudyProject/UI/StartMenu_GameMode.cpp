// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_GameMode.h"
#include "StartMenu_HUD.h"

AStartMenu_GameMode::AStartMenu_GameMode()
{
	HUDClass = AStartMenu_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	//PlayerControllerClass = AController_StartMenu::StaticClass();	// 플레이어 컨트롤러 만들면 마저 넣을것
}

void AStartMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();
}