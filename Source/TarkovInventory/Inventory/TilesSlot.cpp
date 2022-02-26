// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesSlot.h"

#include "TilesWidget.h"
#include "Components/Border.h"

void UTilesSlot::GetIndex2D(int32& X, int32& Y)
{
	X = SlotIndexX;
	Y = SlotIndexY;
}

void UTilesSlot::SetIndex2D(const int32 X, const int32 Y)
{
	SlotIndexX = X;
	SlotIndexY = Y;
}

UTilesWidget* UTilesSlot::GetContainer()
{
	return Cast<UTilesWidget>(GetOuter());
}

void UTilesSlot::SetBackgroundColor(FLinearColor Color)
{
	BackgroundBorder->SetBrushColor(Color);
}