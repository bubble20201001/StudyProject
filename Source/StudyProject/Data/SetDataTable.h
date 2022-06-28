// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "SetDataTable.generated.h"

// 아이템 데이터 테이블(구조체로 만든다)
USTRUCT(BlueprintType)
struct FItemTableInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo");
	int32 ItemUnique;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo");
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo");
	int32 ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo");
	bool IsEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo");
	UTexture2D* ItemIcon;
};

UCLASS()
class STUDYPROJECT_API ASetDataTable : public AActor
{
	GENERATED_BODY()
};
