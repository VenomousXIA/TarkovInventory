// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesWidget.h"

#include "ItemObject.h"
#include "TilesSlot.h"
#include "Components/SizeBox.h"
#include "Components/TileView.h"

FVector2D UTilesWidget::GetEntryDimensions()
{
	return FVector2D(SlotsTileView->GetEntryWidth(), SlotsTileView->GetEntryHeight());
}

void UTilesWidget::GetSlotIndex2D(UTilesSlot* InventorySlot, int32& X, int32& Y)
{
	const int32 SlotIndex = SlotsTileView->GetDisplayedEntryWidgets().Find(InventorySlot);
	if(SlotIndex != INDEX_NONE)
	{
		X = SlotIndex % Cols;
		Y = SlotIndex / Cols;
	}
	else
	{
		X = INDEX_NONE;
		Y = INDEX_NONE;
	}
}

UTilesSlot* UTilesWidget::GetSlotAt(const int32 X, const int32 Y)
{
	if(X < 0 || Y < 0 || X >= Cols || Y >= Rows) return nullptr;
	
	const int32 SlotIndex = Y * Cols + X;
	if(SlotIndex < Cols * Rows)
	{
		UTilesSlot* InventorySlot = static_cast<UTilesSlot*>(SlotsTileView->GetDisplayedEntryWidgets()[SlotIndex]);
		return InventorySlot;
	}
	return nullptr;
}

void UTilesWidget::SetSize()
{
	const FVector2D EntryDimensions = GetEntryDimensions();
	TilesSizeBox->SetWidthOverride(Cols* EntryDimensions.X);
	TilesSizeBox->SetHeightOverride(Rows * EntryDimensions.Y);
}

FVector2D UTilesWidget::GetSize()
{
	return FVector2D(TilesSizeBox->WidthOverride, TilesSizeBox->HeightOverride);
}

void UTilesWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetSize();
	for(int32 i = 0; i < Cols * Rows; i++)
	{
		UItemObject* EmptyItem = NewObject<UItemObject>(this);
		SlotsTileView->AddItem(EmptyItem);
	}
}
