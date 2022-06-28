// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/ListView.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.h"
#include "Item.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	List = Cast<UListView>(GetWidgetFromName(TEXT("InventoryList")));
	List->OnItemClicked().AddUObject(this, &UInventoryWidget::ItemUse);	// ����Ʈ�� ���ȴ°� üũ
}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::PushItemList(FString ItemName, int ItemNum, UTexture2D* Texture)
{
	UItem* item = NewObject<UItem>(this, UItem::StaticClass());

	item->SetItemNum(ItemNum);
	item->SetItemName(ItemName);
	item->SetItemIcon(Texture);

	List->AddItem(item);
	List->RegenerateAllEntries();
}

void UInventoryWidget::PushItemList(FString ItemName, int ItemNum, const FString& strPath)
{
	UItem* item = NewObject<UItem>(this, UItem::StaticClass());

	item->SetItemNum(ItemNum);
	item->SetItemName(ItemName);
	item->SetItemIcon(strPath);

	List->AddItem(item);
	List->RegenerateAllEntries();
}

void UInventoryWidget::ItemUse(UObject* Obj)
{
	// ���� Obj�� UItem���� ����ȯ
	UItem* item = Cast<UItem>(Obj);

	// �������� �������̶�� ������ ���
	if (IsValid(item))
	{
		// ��� �����ϱ�
		return;
	}
}
