// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "SetDataTable.h"

UMyGameInstance::UMyGameInstance()
{
	ItemTableLode();
}

FItemTableInfo* UMyGameInstance::GetItemInfo(int32 ItemUnique)
{
	// �ش� ����ũ�� �������� ���̺� �ִٸ� ������ ����ü ���� ��ȯ
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
		ItemDataTable = DataTable.Object;	// ���̺� �ε尡 �����ϸ� ������ �־��ش�.
	}

	TArray<FItemTableInfo*> arr;
	ItemDataTable->GetAllRows<FItemTableInfo>(TEXT("GetAllRows"), arr);	// ���̺� ���� �ӽù迭�� �ֱ�

	if (IsValid(ItemDataTable))
	{
		for (int32 i = 0; i < arr.Num(); i++)
		{
			ItemInfo.Add(arr[i]->ItemUnique, arr[i]);		// ���Ϳ� ������ ���� ����
		}
	}
}
