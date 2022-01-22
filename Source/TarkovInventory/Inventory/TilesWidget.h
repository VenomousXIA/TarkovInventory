// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TilesWidget.generated.h"

class UCanvasPanel;
class USizeBox;
class UTileView;

class UTilesSlot;
/**
 * 
 */
UCLASS()
class TARKOVINVENTORY_API UTilesWidget : public UUserWidget
{
	GENERATED_BODY()

//Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ExposeOnSpawn="true"))
	int32 Cols;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ExposeOnSpawn="true"))
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
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetSize();

	UFUNCTION(BlueprintCallable)
	FVector2D GetSize();

	virtual void NativeConstruct() override;
};
