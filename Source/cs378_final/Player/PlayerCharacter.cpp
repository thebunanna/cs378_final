// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "cs378_PlayerController.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/PickupInteractable.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckForInteractables();
}

void APlayerCharacter::CheckForInteractables()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);
	Acs378_PlayerController* PController = Cast<Acs378_PlayerController>(GetController());
	if (PController) {
		UInventoryComponent* IController = PController->GetInventory();
		if (!IController) return;
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); iCollected++)
		{
			APickupInteractable* const TestPickup = Cast<APickupInteractable>(CollectedActors[iCollected]);
			// If the cast is successful and the pickup is valid and active 
			if (TestPickup && !TestPickup->IsPendingKill())
			{
				IController->CurrentInteractable = TestPickup;
				return;
			}
		}
		IController->CurrentInteractable = nullptr;
	}

}


