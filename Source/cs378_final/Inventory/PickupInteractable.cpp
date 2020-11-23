// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractable.h"
#include "../Player/cs378_PlayerController.h"
#include "InventoryComponent.h"

APickupInteractable::APickupInteractable()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = Cast<USceneComponent>(PickupMesh);

	ItemID = FName("No ID");

	Super::Name = "Item";
	Super::Action = "pickup";
}

void APickupInteractable::Interact_Implementation(APlayerController* Controller)
{
	Super::Interact_Implementation(Controller);
	if (Controller) {
		UInventoryComponent* IController = Cast<Acs378_PlayerController>(Controller)->GetInventory();
		if (IController->AddItemToInventoryByID(ItemID))
			Destroy();
	}
	
}