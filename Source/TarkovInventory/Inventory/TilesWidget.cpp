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
	const int32 SlotIndex = Y * Cols + X;
	if(SlotIndex >= 0 && SlotIndex < Cols * Rows)
	{
		UTilesSlot* InventorySlot = Cast<UTilesSlot>(SlotsTileView->GetDisplayedEntryWidgets()[SlotIndex]);
		return InventorySlot;
	}
	return nullptr;
}

void UTilesWidget::SetSize()
{
	const FVector2D EntryDimensions = GetEntryDimensions();
	TilesSizeBox->SetWidthOverride(EntryDimensions.X * Cols);
	TilesSizeBox->SetHeightOverride(EntryDimensions.Y * Rows);
}

FVector2D UTilesWidget::GetSize()
{
	return FVector2D(TilesSizeBox->WidthOverride, TilesSizeBox->HeightOverride);
}

bool UTilesWidget::GetEmptyLocation(const int32 DimensionX, const int32 DimensionY, int32& X, int32& Y)
{
	TArray<UUserWidget*> SlotsArray = SlotsTileView->GetDisplayedEntryWidgets();
	for(UUserWidget* SlotWidget: SlotsArray)
	{
		UTilesSlot* TileSlot = static_cast<UTilesSlot*>(SlotWidget);
		if(!TileSlot->IsEmpty) continue;

		int32 SlotX;
		int32 SlotY;
		GetSlotIndex2D(TileSlot, SlotX, SlotY);
		if(SlotX + DimensionX > Cols || SlotY + DimensionY > Rows) continue;

		bool IsSuitable = true;
		for(int32 i = SlotX; i < SlotX + DimensionX; i++)
		{
			for(int32 j = SlotY; j < SlotY + DimensionY; j++)
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

void UTilesWidget::GetProperLocation(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY, int32& ProperX,
	int32& ProperY)
{
	ProperX = X - (DimensionX / 2);
	ProperY = Y - (DimensionY / 2);
	ClampLocation(DimensionX, DimensionY, ProperX, ProperY);
}

bool UTilesWidget::IsValidDropLocation(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY)
{
	for(int32 i = X; i < X + DimensionX; i++)
	{
		for(int32 j = Y; j < Y + DimensionY; j++)
		{
			if(!GetSlotAt(i, j)->IsEmpty) return false;
		}
	}
	return true;
}

void UTilesWidget::HighlightSpace(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY,
	ESpaceAvailability Availability)
{
	FLinearColor Color;
	switch (Availability)
	{
	case ESpaceAvailability::Available:
		Color = FLinearColor(0.0f, 0.2f, 0.0f, 0.3f);
		break;
	case ESpaceAvailability::NotAvailable:
		Color = FLinearColor(0.2f, 0.0f, 0.0f, 0.3f);
		break;
	case ESpaceAvailability::Default:
		Color = FLinearColor(0.0f, 0.0f, 0.0f, 0.3f);
		break;
	case ESpaceAvailability::AutoHandle:
		Availability = GetSpaceAvailability(X, Y, DimensionX, DimensionY);
		HighlightSpace(X, Y, DimensionX, DimensionY, Availability);
		return;
	case ESpaceAvailability::Reset:
		Color = FLinearColor(0.0f, 0.0f, 0.0f, 0.3f);
		for(int32 i = 0; i < Cols; i++)
		{
			for(int32 j = 0; j < Rows; j++)
			{
				GetSlotAt(i, j)->SetBackgroundColor(Color);
			}
		}
		return;
	default: return;
	}

	for(int32 i = X; i < X + DimensionX; i++)
	{
		for(int32 j = Y; j < Y + DimensionY; j++)
		{
			GetSlotAt(i, j)->SetBackgroundColor(Color);
		}
	}
}

ESpaceAvailability UTilesWidget::GetSpaceAvailability(const int32 X, const int32 Y, const int32 DimensionX,
	const int32 DimensionY)
{
	if(IsValidDropLocation(X, Y, DimensionX, DimensionY))
	{
		return ESpaceAvailability::Available;
	}
	
	return ESpaceAvailability::NotAvailable;
}

void UTilesWidget::ClampLocation(const int32 DimensionX, const int32 DimensionY, int32& X, int32& Y)
{
	if(X < 0) X = 0;
	if(Y < 0) Y = 0;

	if(X + DimensionX > Cols) X = Cols - DimensionX;
	if(Y + DimensionY > Rows) Y = Rows - DimensionY;
}

void UTilesWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Warning, TEXT("Tiles Construction Script..."))
	if(SlotsTileView->GetNumItems() < Cols * Rows)
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling Super Construction Script..."))
		Super::NativeConstruct();
		while(SlotsTileView->GetNumItems() < Cols * Rows)
		{
			UItemObject* Item = NewObject<UItemObject>(this);
			SlotsTileView->AddItem(Item);
		}
		SetSize();	
	}
}