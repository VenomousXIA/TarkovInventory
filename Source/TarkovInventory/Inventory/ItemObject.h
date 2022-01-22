// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta=(IsBlueprintBase="true"))
class TARKOVINVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ExposeOnSpawn="true"))
	int32 SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ExposeOnSpawn="true"))
	int32 SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ExposeOnSpawn="true", DisplayThumbnail="true"))
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta=(ExposeOnSpawn="true"))
	UClass* ItemClass;
};
