// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "ItemObject.h"
#include "TilesWidget.h"
#include "Components/SizeBox.h"

void UItemWidget::SetSize(const float Width, const float Height)
{
	ItemSizeBox->SetWidthOverride(Item->SizeX * Width);
	ItemSizeBox->SetHeightOverride(Item->SizeY * Height);
}

FVector2D UItemWidget::GetSize()
{
	return FVector2D(ItemSizeBox->WidthOverride, ItemSizeBox->HeightOverride);
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(Item)
	{
		SetSize(60.0f, 60.0f);
	}
}
