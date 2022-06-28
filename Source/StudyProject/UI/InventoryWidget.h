// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UListView* List;

public:
	// ����Ʈ�� Data Push
	void PushItemList(FString ItemName, int ItemNum, UTexture2D * Texture);
	void PushItemList(FString ItemName, int ItemNum, const FString& strPath);

	// ������ ���
	void ItemUse(UObject* Obj);
};
