// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableBase.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CS378_FINAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION()
		void Interact();

	UFUNCTION()
		void ReloadInventory();

	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool AddItemToInventoryByID(FName ID, TSubclassOf<class AActor> base, ItemType Type, int32 val);
	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool RemoveFromInventory(FInventoryItem item, bool spawn);
	UFUNCTION(BlueprintCallable, Category = "Utils")
		bool UseItem(FInventoryItem item);


	class IInteractableBase* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 InventorySlotLimit;

	
protected:
	// Called when the game starts

			
};
