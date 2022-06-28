// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* ItemNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* ItemIcon;

public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetItemData(class UItem* ItemData);	// class 표시 붙일것. 안붙이니 호환 안됌.
};
