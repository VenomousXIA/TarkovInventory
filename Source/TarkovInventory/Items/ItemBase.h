// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UItemObject;
class UTilesWidget;

UCLASS()
class TARKOVINVENTORY_API AItemBase : public AActor
{
	GENERATED_BODY()

	//Properties
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected", meta=(ExposeOnSpawn="true"));
	int32 InventorySizeX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected", meta=(ExposeOnSpawn="true"));
	int32 InventorySizeY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected", meta=(ExposeOnSpawn="true"));
	FSlateBrush InventoryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected", meta=(ExposeOnSpawn="true"));
	UTilesWidget* ItemsContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected", meta=(ExposeOnSpawn="true"))
	int32 ContainerCols;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Protected", meta=(ExposeOnSpawn="true"))
	int32 ContainerRows;

	//Functions
public:
	UFUNCTION(BlueprintPure)
	void GetContainerDimensions(int32& Cols, int32& Rows) const {Cols = ContainerCols, Rows = ContainerRows;};

	UFUNCTION(BlueprintPure)
	void GetItemDimensions(int32& SizeX, int32& SizeY) const {SizeX = InventorySizeX, SizeY = InventorySizeY;};
	
	UFUNCTION(BlueprintCallable)
	void RotateItem() {InventorySizeX = InventorySizeX + InventorySizeY, InventorySizeY = InventorySizeX - InventorySizeY, InventorySizeX = InventorySizeX - InventorySizeY;};
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
