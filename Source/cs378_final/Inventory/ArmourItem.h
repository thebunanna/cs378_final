// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include <RPGCharacter/Equipment/Armor.h>

#include "ArmourItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CS378_FINAL_API FArmourItem : public FTableRowBase
{
	GENERATED_BODY()
public:

	FArmourItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class TSubclassOf<class AArmor> actor;
};
