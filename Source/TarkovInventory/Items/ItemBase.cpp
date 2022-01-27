// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "TarkovInventory/Inventory/ItemObject.h"
#include "TarkovInventory/Inventory/TilesWidget.h"

UItemObject* AItemBase::ConstructItemObject(UTilesWidget* Container)
{
	UItemObject* Item = NewObject<UItemObject>(Container);
	Item->SizeX = InventorySizeX;
	Item->SizeY = InventorySizeY;
	Item->Icon = InventoryIcon;
	Item->ItemClass = GetClass();
	Item->ItemScale = GetRootComponent()->GetComponentScale();
	return Item;
}

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

