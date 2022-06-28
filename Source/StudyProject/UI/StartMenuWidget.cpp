// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UStartMenuWidget::NativeConstruct()
{
	if (Btn_StartGame)
		Btn_StartGame->OnClicked.AddDynamic(this, &UStartMenuWidget::Btn_StartGame_Clicked);

	if (Btn_ExitGame)
		Btn_ExitGame->OnClicked.AddDynamic(this, &UStartMenuWidget::Btn_ExitGame_Clicked);
}

void UStartMenuWidget::Btn_StartGame_Clicked()
{
	// �ʵ巹�� ����
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/_My/Map01");
}

void UStartMenuWidget::Btn_ExitGame_Clicked()
{
	// ���� �ߴ�
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}