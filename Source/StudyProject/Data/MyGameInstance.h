// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/*
������ ���̺��� �Һ� �������̹Ƿ� ���� �ʱ�ȭ�Ҷ��� �ε��ϸ� �ȴ�.
��Ÿ ���̺� �ε�� ���ʿ��� �� ��
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
	TMap<int32, FItemTableInfo*> ItemInfo;	// UDataTable���� �̸��� ã�ƽᵵ �ǳ� ������ �����ϴ°��� �� ���ؼ� �� ���
};
