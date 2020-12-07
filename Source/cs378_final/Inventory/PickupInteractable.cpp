// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractable.h"
#include "../Player/cs378_PlayerController.h"
#include "InventoryComponent.h"


APickupInteractable::APickupInteractable()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = Cast<USceneComponent>(PickupMesh);

	ItemID = FName("No ID");

	Name = "Item";
	Action = "pickup";
}

void APickupInteractable::Interact_Implementation(APlayerController* Controller)
{
	if (Controller) {
		UInventoryComponent* InvController = Cast<Acs378_PlayerController>(Controller)->GetInventory();
		if (InvController->AddItemToInventoryByID(ItemID, this->GetClass(), this->Type, GetValue()))
			Destroy();
	}
	
}

FString APickupInteractable::GetInteractText() const
{
	return FString::Printf(TEXT("%s: Press F to %s"), *Name, *Action);
}
