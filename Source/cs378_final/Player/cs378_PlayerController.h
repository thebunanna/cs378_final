// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "cs378_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CS378_FINAL_API Acs378_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	Acs378_PlayerController();

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UInventoryComponent* Inv;

public:
	void Forward(float value);
	void Right(float value);
	void CameraY(float value);
	void CameraX(float value);

	void Attack();
	void Pickup();

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventory();
};
