// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "ItemObject.h"
#include "TilesWidget.h"
#include "Components/SizeBox.h"

void UItemWidget::SetSize()
{
	if(Item && Container)
	{
		const FVector2D EntryDimensions = Container->GetEntryDimensions();
		if(Item->IsContainer && Container->Cols == 1 && Container->Rows == 1)
		{
			ItemSizeBox->SetWidthOverride(Item->SizeX * EntryDimensions.X / 2);
			ItemSizeBox->SetHeightOverride(Item->SizeY * EntryDimensions.Y / 2);
		}
		else
		{
			ItemSizeBox->SetWidthOverride(Item->SizeX * EntryDimensions.X);
			ItemSizeBox->SetHeightOverride(Item->SizeY * EntryDimensions.Y);
		}
		
	}
}

FVector2D UItemWidget::GetSize()
{
	return FVector2D(ItemSizeBox->WidthOverride, ItemSizeBox->HeightOverride);
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(Item && Container)
	{
		SetSize();
	}
}
