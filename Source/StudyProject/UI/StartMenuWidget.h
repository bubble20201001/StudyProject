// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartMenuWidget.generated.h"

/*
 프로퍼티 메타를 BindWidget로 지정해주면 선언한 변수와 똑같은 이름의 구성요소가 있어야 제대로 돌아간다.
 */
UCLASS()
class STUDYPROJECT_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_StartGame = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_ExitGame = nullptr;

private:
	UFUNCTION()
	void Btn_StartGame_Clicked();

	UFUNCTION()
	void Btn_ExitGame_Clicked();

};
