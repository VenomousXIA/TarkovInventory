// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "TilesSlot.generated.h"

class UBorder;

class UTilesWidget;
/**
 * 
 */
UCLASS()
class TARKOVINVENTORY_API UTilesSlot : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

//Properties
public:
	UPROPERTY(BlueprintReadWrite, Category="Default")
	bool IsEmpty = true;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="GUI Widget", meta=(BindWidgetOptional))
	UBorder* BackgroundBorder;
	
private:
	int32 SlotIndexX;
	
	int32 SlotIndexY;

//Functions
public:
	UFUNCTION(BlueprintPure)
	void GetIndex2D(int32& X, int32& Y);

	UFUNCTION(BlueprintPure)
	UTilesWidget* GetContainer();
	
	UFUNCTION(BlueprintCallable)
	void SetBackgroundColor(FLinearColor Color);
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
