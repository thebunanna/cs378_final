// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "InteractableBase.h"
#include "Templates/SubclassOf.h"
#include "InventoryItem.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class ItemType : uint8 {
	MISC = 0 UMETA(DisplayName = "Misc"),
	ARMOR = 1  UMETA(DisplayName = "Armour"),
	WEAPON = 2     UMETA(DisplayName = "Weapon"),
	CONSUMABLES = 3 UMETA(DisplayName = "Consumables"),
	OTHER = 4 UMETA(DisplayName = "Other")
};

USTRUCT (BlueprintType)
struct CS378_FINAL_API FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

private:
	

public:
	FInventoryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class TSubclassOf<class AActor> actor;

	bool operator==(const FInventoryItem& OtherItem) const
	{
		if (ItemID == OtherItem.ItemID)
			return true;
		return false;
	}
};
