// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"

#include <RPGCharacter/Player/ModularPlayerController.h>
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "../Inventory/UI/InventoryWidget.h"
#include "cs378_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CS378_FINAL_API Acs378_PlayerController : public AModularPlayerController
{
	GENERATED_BODY()

public:
	Acs378_PlayerController();

protected:
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Inventory)
		class UInventoryComponent* Inv;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
		class TSubclassOf<class UInventoryWidget> BP_InvWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
		UInventoryWidget* IW;

	UFUNCTION(BlueprintCallable)
		UInventoryComponent* GetInventory();

	UFUNCTION(BlueprintCallable)
		void LoadInvWidget();

	UFUNCTION(BlueprintImplementableEvent)
		void ReloadInventory();
};
