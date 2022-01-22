// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "ItemObject.h"
#include "TilesWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UItemWidget::SetSize()
{
	if(Item && Container)
	{
		const FVector2D EntryDimensions = Container->GetEntryDimensions();
		ItemSizeBox->SetWidthOverride(Item->SizeX * EntryDimensions.X);
		ItemSizeBox->SetHeightOverride(Item->SizeY * EntryDimensions.Y);
	}
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
		Container = static_cast<UTilesWidget*>(Item->GetOuter());
		if(Container)
		{
			SetSize();
			ItemImage->SetBrushFromTexture(Item->Icon, true);
		}
	}
}
