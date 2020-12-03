// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Player/cs378_PlayerController.h"
#include "../CS378FinalGameState.h"
#include "InventoryItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InventorySlotLimit = 50;

	// ...
}


bool UInventoryComponent::AddItemToInventoryByID(FName ID)
{
	ACS378FinalGameState* GameState = Cast<ACS378FinalGameState>(GetWorld()->GetGameState());

	if (GameState == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("GAME STATE NOT EXIST"));
		return false;
	}

	UDataTable* ItemTable = GameState->GetItemDB();

	if (ItemTable == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("ITEM TABLE IS NULL"));
		return false;
	}

	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

	
	if (ItemToAdd)
	{
		if (Inventory.Num() < InventorySlotLimit)
		{
			Inventory.Add(*ItemToAdd);
			ReloadInventory();
			return true;
		}
	}
	
	
	return false;
}

void UInventoryComponent::Interact()
{
	
	if (CurrentInteractable)
	{
		CurrentInteractable->Execute_Interact(Cast<UObject>(CurrentInteractable), Cast<Acs378_PlayerController>(GetOwner()));
	}
}

void UInventoryComponent::ReloadInventory()
{
	Cast<Acs378_PlayerController>(GetOwner())->ReloadInventory();
}
