// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Item.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemNum")));
	ItemIcon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));

}

void UItemWidget::SetItemData(class UItem* ItemData)
{
	if (ItemName && ItemNum)
	{
		FString str = "";
		str = FString::Printf(TEXT("%d"), ItemData->GetItemNum());
		ItemNum->SetText(FText::FromString(str));

		ItemName->SetText(FText::FromString(ItemData->GetItemName()));
		ItemIcon->SetBrushFromTexture(ItemData->GetItemIcon());
	}
}