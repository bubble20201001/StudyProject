// Copyright Epic Games, Inc. All Rights Reserved.


#include "StudyProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "InventoryWidget.h"

AStudyProjectGameModeBase::AStudyProjectGameModeBase()
{
	// 월드에 위젯 생성
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

	// 화면에 뿌려줌
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
	}

	// FClassFinder(애셋의 타입(형)을 가져옴) / FObjectFinder(에셋의 내용물을 가져옴)는 꼭 생성자에서 사용할 것(안그럼 에러남)
	// 애초에 ConstructorHelpers 자체가 생성자에서만 사용이 가능하다. 게임 플레이 도중 특정 애셋을 사용한 무언가를 사용하려고 했을 때 그 에셋이 없다면 해당 콘텐츠는 크래시가 나기 때문(안전문제)
	// 엔진 초기화 런타임이 아닌 게임플레이 런타임 시점에서 꼭 에셋을 불러오고 싶다면 StaticLoadClass를 사용할것
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUI(TEXT("/Game/_My/UI/UI_Inventory"));
	if (InventoryUI.Succeeded())
	{
		uiInventoryBPClass = InventoryUI.Class;	// 제대로 불러왔다면 변수에 넣어준다
	}
	if (uiInventoryBPClass)
	{
		uiInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), uiInventoryBPClass);	// 위젯 생성
		if (uiInventoryWidget)
		{
			uiInventoryWidget->AddToViewport(); // 위젯이 정상적으로 있다면 화면에 뿌려준다
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
