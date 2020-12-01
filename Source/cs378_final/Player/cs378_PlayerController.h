// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"

#include <RPGCharacter/Player/ModularPlayerController.h>
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
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
	UFUNCTION(BlueprintCallable)
		UInventoryComponent* GetInventory();

	UFUNCTION(BlueprintImplementableEvent)
		void ReloadInventory();
};
