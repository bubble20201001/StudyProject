// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/*
아이템 테이블은 불변 데이터이므로 앱을 초기화할때만 로드하면 된다.
기타 테이블 로드로 이쪽에서 할 것
 */

struct FItemTableInfo;
class UDataTable;

UCLASS()
class STUDYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

public:
	FItemTableInfo* GetItemInfo(int32 ItemUnique);

	void ItemTableLode();

private:
	UDataTable* ItemDataTable;
	TMap<int32, FItemTableInfo*> ItemInfo;	// UDataTable에서 이름을 찾아써도 되나 맵으로 관리하는것이 더 편해서 맵 사용
};
