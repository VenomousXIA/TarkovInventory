// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TilesWidget.generated.h"

class UCanvasPanel;
class USizeBox;
class UTileView;

class UTilesSlot;
class UItemObject;

UENUM()
enum class ESpaceAvailability: uint8
{
	Available,
	NotAvailable,
	AutoHandle,
	Reset,
	Default
};
/**
 * 
 */
UCLASS()
class TARKOVINVENTORY_API UTilesWidget : public UUserWidget
{
	GENERATED_BODY()

	//Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	int32 Cols;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	int32 Rows;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	UCanvasPanel* TilesCanvas;

	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	USizeBox* TilesSizeBox;

	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	UTileView* SlotsTileView;

	//Functions
	public:
	UFUNCTION(BlueprintCallable)
	FVector2D GetEntryDimensions();

	UFUNCTION(BlueprintCallable)
	void GetSlotIndex2D(UTilesSlot* InventorySlot, int32& X, int32& Y);

	UFUNCTION(BlueprintCallable)
	UTilesSlot* GetSlotAt(const int32 X, const int32 Y);

	UFUNCTION(BlueprintCallable)
	bool GetEmptyLocation(const int32 DimensionX, const int32 DimensionY, int32& X, int32& Y);

	UFUNCTION(BlueprintCallable)
	void SetSlotsEmptyState(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY, const bool IsEmpty);

	UFUNCTION(BlueprintCallable)
	void GetProperLocation(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY, int32& ProperX, int32& ProperY);

	UFUNCTION(BlueprintCallable)
	bool IsValidDropLocation(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY);

	UFUNCTION(BlueprintCallable)
	void HighlightSpace(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY, ESpaceAvailability Availability);
	
	UFUNCTION(BlueprintCallable)
	ESpaceAvailability GetSpaceAvailability(const int32 X, const int32 Y, const int32 DimensionX, const int32 DimensionY);
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetSize();

	virtual void NativeConstruct() override;

private:
	void ClampLocation(const int32 DimensionX, const int32 DimensionY, int32& X, int32& Y);
};
