// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TarkovInventory/Items/ItemBase.h"
#include "ItemObject.generated.h"

class UTilesWidget;

/**
 * 
 */
UCLASS(Blueprintable)
class TARKOVINVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()

//Properties
public:
	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	int32 SizeX;

	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	int32 SizeY;

	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true", DisplayThumbnail="true"))
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	TSubclassOf<AItemBase> ItemClass;

	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	FVector ItemScale;
	
	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	UTilesWidget* ItemsContainer = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	int32 ContainerCols;

	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	int32 ContainerRows;
	
	UPROPERTY(BlueprintReadWrite, Category="Public", meta=(ExposeOnSpawn="true"))
	bool IsContainer = false;
	
//Functions
public:
	UFUNCTION(BlueprintPure)
	void GetDimensions(int32& X, int32& Y) const {X = SizeX, Y = SizeY;}

	UFUNCTION(BlueprintPure)
	void GetContainerDimensions(int32& Cols, int32& Rows) const {Cols = ContainerCols, Rows = ContainerRows;};
};
