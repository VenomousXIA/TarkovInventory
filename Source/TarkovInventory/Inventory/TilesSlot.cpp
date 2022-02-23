// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesSlot.h"

#include "TilesWidget.h"
#include "ItemObject.h"
#include "Components/Border.h"

void UTilesSlot::GetIndex2D(int32& X, int32& Y)
{
	X = SlotIndexX;
	Y = SlotIndexY;
}

UTilesWidget* UTilesSlot::GetContainer()
{
	UObject* Item = GetListItem<UItemObject>()->GetOuter();
	if(Item)
	{
		UTilesWidget* Container = Cast<UTilesWidget>(Item);
		return Container;
	}

	return nullptr;
}

void UTilesSlot::SetBackgroundColor(FLinearColor Color)
{
	BackgroundBorder->SetBrushColor(Color);
}

void UTilesSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	bIsFocusable = false;

	UTilesWidget* Container = static_cast<UTilesWidget*>(ListItemObject->GetOuter());
	if(Container)
	{
		Container->GetSlotIndex2D(this, SlotIndexX, SlotIndexY);
	}
	else
	{
		SlotIndexX = INDEX_NONE;
		SlotIndexY = INDEX_NONE;
	}
}
