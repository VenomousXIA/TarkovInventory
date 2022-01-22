// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesWidget.h"

#include "ItemObject.h"
#include "TilesSlot.h"
#include "Components/SizeBox.h"
#include "Components/TileView.h"

FVector2D UTilesWidget::GetEntryDimensions()
{
	UE_LOG(LogTemp, Warning, TEXT("Entry Width - %i, Entry Height - %i"), this->SlotsTileView->GetEntryWidth(), SlotsTileView->GetEntryHeight())
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

bool UTilesWidget::GetEmptyLocation(UItemObject* Item, int32& X, int32& Y)
{
	TArray<UUserWidget*> SlotsArray = SlotsTileView->GetDisplayedEntryWidgets();
	for(UUserWidget* SlotWidget: SlotsArray)
	{
		UTilesSlot* TileSlot = static_cast<UTilesSlot*>(SlotWidget);
		if(!TileSlot->IsEmpty) continue;

		int32 SlotX;
		int32 SlotY;
		GetSlotIndex2D(TileSlot, SlotX, SlotY);
		if(SlotX + Item->SizeX > Cols || SlotY + Item->SizeY > Rows) continue;

		bool IsSuitable = true;
		for(int32 i = SlotX; i < SlotX + Item->SizeX; i++)
		{
			for(int32 j = SlotY; j < SlotY + Item->SizeY; j++)
			{
				if(!GetSlotAt(i, j)->IsEmpty)
				{
					IsSuitable = false;
					break;
				}
			}
			if(!IsSuitable)
			{
				break;
			}
		}
		if(IsSuitable)
		{
			X = SlotX;
			Y = SlotY;
			return true;
		}
	}
	X = INDEX_NONE;
	Y = INDEX_NONE;
	return false;
}

void UTilesWidget::SetSlotsEmptyState(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY,
	const bool IsEmpty)
{
	if(X < 0 || Y < 0 || X + DimensionX > Cols || Y + DimensionY > Rows) return;
	
	for(int32 i = X; i < X + DimensionX; i++)
	{
		for(int32 j = Y; j < Y + DimensionY; j++)
		{
			GetSlotAt(i, j)->IsEmpty = IsEmpty;
		}
	}
}

void UTilesWidget::GetProperLocation(const UItemObject* Item, const int32 X, const int32 Y, int32& ProperX, int32& ProperY)
{
	ProperX = X - (Item->SizeX / 2);
	ProperY = Y - (Item->SizeY / 2);
	ClampLocation(Item, ProperX, ProperY);
}

bool UTilesWidget::IsValidDropLocation(const UItemObject* Item, const int32 X, const int32 Y)
{
	for(int32 i = X; i < X + Item->SizeX; i++)
	{
		for(int32 j = Y; j < Y + Item->SizeY; j++)
		{
			if(!GetSlotAt(i, j)->IsEmpty) return false;
		}
	}
	return true;
}

void UTilesWidget::ClampLocation(const UItemObject* Item, int32& X, int32& Y)
{
	if(X < 0) X = 0;
	if(Y < 0) Y = 0;

	if(X + Item->SizeX > Cols) X = Cols - Item->SizeX;
	if(Y + Item->SizeY > Rows) Y = Rows - Item->SizeY;
}

void UTilesWidget::SetSize()
{
	const FVector2D EntryDimensions = GetEntryDimensions();
	TilesSizeBox->SetWidthOverride(Cols* EntryDimensions.X);
	TilesSizeBox->SetHeightOverride(Rows * EntryDimensions.Y);
}

FVector2D UTilesWidget::GetSize()
{
	return 	FVector2D(TilesSizeBox->WidthOverride, TilesSizeBox->HeightOverride);
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
