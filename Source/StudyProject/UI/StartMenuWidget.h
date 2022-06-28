// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartMenuWidget.generated.h"

/*
 ������Ƽ ��Ÿ�� BindWidget�� �������ָ� ������ ������ �Ȱ��� �̸��� ������Ұ� �־�� ����� ���ư���.
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
