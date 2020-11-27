// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "PickupInteractable.generated.h"

/**
 * 
 */
UCLASS()
class CS378_FINAL_API APickupInteractable : public AInteractableBase
{
	GENERATED_BODY()

public:
	APickupInteractable();

	void Interact_Implementation(APlayerController* Controller) override;

protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;
};