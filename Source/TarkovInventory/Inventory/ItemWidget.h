// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class USizeBox;
class UBorder;
class UImage;

class UItemObject;
class UTilesWidget;
/**
 * 
 */
UCLASS()
class TARKOVINVENTORY_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

// Properties
public:
	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn))
	UItemObject* Item;

	UPROPERTY(BlueprintReadWrite, Category="Public")
	int32 InventoryX;
	
	UPROPERTY(BlueprintReadWrite, Category="Public")
	int32 InventoryY;

protected:
	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	USizeBox* ItemSizeBox;
	
	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	UBorder* BackgroundBorder;

	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	UImage* ItemImage;

//Functions
protected:
	UFUNCTION(BlueprintCallable)
	void SetSize(const float Width, const float Height);

	UFUNCTION(BlueprintCallable)
	void SetInventoryLocation(const int32 X, const int32 Y) {InventoryX =  X, InventoryY = Y;};

	UFUNCTION(BlueprintPure)
	void GetInventoryLocation(int32& X, int32& Y) {X = InventoryX, Y = InventoryY;}
	
	UFUNCTION(BlueprintPure)
	FVector2D GetSize();

	virtual void NativeConstruct() override;
};
