// Copyright Epic Games, Inc. All Rights Reserved.


#include "StudyProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "InventoryWidget.h"

AStudyProjectGameModeBase::AStudyProjectGameModeBase()
{
	// ���忡 ���� ����
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

	// ȭ�鿡 �ѷ���
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
	}

	// FClassFinder(�ּ��� Ÿ��(��)�� ������) / FObjectFinder(������ ���빰�� ������)�� �� �����ڿ��� ����� ��(�ȱ׷� ������)
	// ���ʿ� ConstructorHelpers ��ü�� �����ڿ����� ����� �����ϴ�. ���� �÷��� ���� Ư�� �ּ��� ����� ���𰡸� ����Ϸ��� ���� �� �� ������ ���ٸ� �ش� �������� ũ���ð� ���� ����(��������)
	// ���� �ʱ�ȭ ��Ÿ���� �ƴ� �����÷��� ��Ÿ�� �������� �� ������ �ҷ����� �ʹٸ� StaticLoadClass�� ����Ұ�
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUI(TEXT("/Game/_My/UI/UI_Inventory"));
	if (InventoryUI.Succeeded())
	{
		uiInventoryBPClass = InventoryUI.Class;	// ����� �ҷ��Դٸ� ������ �־��ش�
	}
	if (uiInventoryBPClass)
	{
		uiInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), uiInventoryBPClass);	// ���� ����
		if (uiInventoryWidget)
		{
			uiInventoryWidget->AddToViewport(); // ������ ���������� �ִٸ� ȭ�鿡 �ѷ��ش�
		}
	}
}

void AStudyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AStudyProjectGameModeBase::ChangeUI()
{
	//CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	//CurrentWidget->AddToViewport();
}
