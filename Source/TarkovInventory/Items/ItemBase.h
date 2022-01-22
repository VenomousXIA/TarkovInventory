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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default");
	int32 InventorySizeX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default");
	int32 InventorySizeY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default");
	UTexture2D* InventoryIcon;
	
//Functions
public:
	UFUNCTION(BlueprintCallable)
	UItemObject* ConstructItemObject(UTilesWidget* Container);



	
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
