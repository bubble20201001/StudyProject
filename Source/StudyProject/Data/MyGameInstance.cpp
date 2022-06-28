// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "SetDataTable.h"

UMyGameInstance::UMyGameInstance()
{
	ItemTableLode();
}

FItemTableInfo* UMyGameInstance::GetItemInfo(int32 ItemUnique)
{
	// 해당 유니크의 아이템이 테이블에 있다면 아이템 구조체 정보 반환
	if (ItemInfo.Find(ItemUnique) != nullptr)
	{
		return ItemInfo[ItemUnique];
	}

	return nullptr;
}

void UMyGameInstance::ItemTableLode()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("DataTable'/Game/_My/DataTable/ItemDataTable.ItemDataTable'"));
	if (DataTable.Succeeded())
	{
		ItemDataTable = DataTable.Object;	// 테이블 로드가 성공하면 변수에 넣어준다.
	}

	TArray<FItemTableInfo*> arr;
	ItemDataTable->GetAllRows<FItemTableInfo>(TEXT("GetAllRows"), arr);	// 테이블 정보 임시배열에 넣기

	if (IsValid(ItemDataTable))
	{
		for (int32 i = 0; i < arr.Num(); i++)
		{
			ItemInfo.Add(arr[i]->ItemUnique, arr[i]);		// 벡터에 아이템 정보 삽입
		}
	}
}
