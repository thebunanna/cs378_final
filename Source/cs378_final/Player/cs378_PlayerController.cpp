// Fill out your copyright notice in the Description page of Project Settings.


#include "cs378_PlayerController.h"
#include "../Inventory/InventoryComponent.h"


Acs378_PlayerController::Acs378_PlayerController()
{
	Inv = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void Acs378_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, Inv, &UInventoryComponent::Interact);
	//if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::White,
	//	           TEXT("HI there"));
}


UInventoryComponent* Acs378_PlayerController::GetInventory()
{
	return this->Inv;
}
