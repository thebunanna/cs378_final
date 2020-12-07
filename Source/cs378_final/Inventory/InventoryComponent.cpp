// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Player/cs378_PlayerController.h"
#include "../CS378FinalGameState.h"
#include "InventoryItem.h"
#include "ArmourItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InventorySlotLimit = 50;

	// ...
}


bool UInventoryComponent::AddItemToInventoryByID(FName ID, TSubclassOf<class AActor> base, ItemType Type, int32 val)
{
	static int32 uid = 0;

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

	FInventoryItem* ItemTemplate = ItemTable->FindRow<FInventoryItem>(ID, "");

	
	if (ItemTemplate)
	{
		FInventoryItem NewItem = *ItemTemplate;

		NewItem.ItemID.SetNumber(uid++);
		NewItem.actor = base;
		NewItem.Type = Type;
		NewItem.Value = val;
		if (Inventory.Num() < InventorySlotLimit)
		{
			Inventory.Add(NewItem);
			ReloadInventory();
			return true;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Max Slots reached."));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Not Found."));
		return false;
	}
	
	return false;
}

bool UInventoryComponent::RemoveFromInventory(FInventoryItem item, bool spawn)
{
	int32 num = Inventory.Remove(item);
	if (num > 1)
		UE_LOG(LogTemp, Warning, TEXT("More than 1 item has been destoryed!"));

	
	if (spawn) {
		if (item.actor.Get() != NULL) {
			TSubclassOf<AActor> ActorClass = *item.actor;
			FActorSpawnParameters sp = FActorSpawnParameters();
			APlayerController* pc = Cast<APlayerController>(GetOwner());
			if (pc != NULL) {
				APawn* p = pc->GetPawn<APawn>();
				FTransform trans = p->GetTransform();
				if (GetWorld()->SpawnActor(ActorClass, &trans, sp) == NULL)
					UE_LOG(LogTemp, Warning, TEXT("Spawning failed Non Actor"));
			}
			else {
				return false;
			}
		}
		else 
			UE_LOG(LogTemp, Warning, TEXT("Spawning failed"));

	}
	
	
	
	return false;
}

bool UInventoryComponent::UseItem(FInventoryItem item)
{
	int32 ind = Inventory.Find(item);
	if (ind == INDEX_NONE) {
		UE_LOG(LogTemp, Warning, TEXT("ITEM INVALID"));
		return false;
	}

	if (item.Type == ItemType::ARMOR) {
		APlayerController* pc = Cast<APlayerController>(GetOwner());
		if (pc != NULL) {
			AModularPlayerCharacter* ModPawn = pc->GetPawn<AModularPlayerCharacter>();
			if (ModPawn != NULL) {

				ACS378FinalGameState* GameState = Cast<ACS378FinalGameState>(GetWorld()->GetGameState());

				if (GameState == NULL) {
					UE_LOG(LogTemp, Warning, TEXT("GAME STATE NOT EXIST"));
					return false;
				}

				UDataTable* ArmorTable = GameState->GetArmorDB();

				if (ArmorTable == NULL) {
					UE_LOG(LogTemp, Warning, TEXT("ARMOR TABLE IS NULL"));
					return false;
				}

				

				FName search = ArmorTable->GetRowNames()[item.Value];				
				FArmourItem* Armour = ArmorTable->FindRow<FArmourItem>(search, "");

				if (Armour != NULL) {
					ModPawn->EquipArmor(Armour->actor);
					/*
					FActorSpawnParameters sp = FActorSpawnParameters();
					FTransform trans = ModPawn->GetTransform();

					AArmor* created_armour = Cast<AArmor>(GetWorld()->SpawnActor(Armour->actor, &trans, sp));

					if (created_armour != NULL) {
					}
					else
						UE_LOG(LogTemp, Warning, TEXT("Spawning failed Non Armour"));
					
					*/
					
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("ARMOR VALUE IS INVALID"));
					return false;
				}

			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Non modular character. can't equip"));
			}
		}
		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Unusable? remove when all implemnted"));
		return false;

	}
	return true;
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
