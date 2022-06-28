// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
enum eITEMTYPE
{
	ITEMTYPE_FOOD,
	ITEMTYPE_FARM,

	ITEMTYPE_MAX,
};

// UListBox는 Object형을 받기 때문에 Object 클래스를 상속받는 아이템 클래스를 생성하여 아이템 정보를 넣어준다
UCLASS(Blueprintable, BlueprintType)
class STUDYPROJECT_API UItem : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int ItemNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UTexture2D* IconTexture;

public:
	int GetItemNum() const { return ItemNum; }
	void SetItemNum( int num ) { ItemNum = num; }

	FString GetItemName() const { return ItemName; }
	void SetItemName(FString name) { ItemName = name; }
	
	UTexture2D* GetItemIcon() const { return IconTexture; }
	void SetItemIcon(UTexture2D* Texture) { IconTexture = Texture; }
	void SetItemIcon(const FString& strPath) { IconTexture = LoadObject<UTexture2D>(nullptr, *strPath); }
};
