// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "../../Player//cs378_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../InventoryComponent.h"

void UInventoryWidget::LoadInventory()
{
	if (BP_InvSlot.Get() == NULL || InvPanel == NULL ) {
		UE_LOG(LogTemp, Warning, TEXT("bp not set!"));
		return;
	}

	if (IsVisible()) {
		InvPanel->ClearChildren();

		if (LinkedInv == NULL) {
			UE_LOG(LogTemp, Warning, TEXT("Not Linked!"));
			return;
		}

		/*
		UInventoryComponent* Inventory = Cast<UInventoryComponent>(LinkedInv);

		if (Inventory == NULL) {
			UE_LOG(LogTemp, Warning, TEXT("No inventory!"));
			return;
		}

		*/
		
		
		APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
		if (Controller != NULL) {
			Acs378_PlayerController* pc = Cast<Acs378_PlayerController>(Controller);
			if (pc == NULL) {
				UE_LOG(LogTemp, Warning, TEXT("non valid pc "));
			}
			else {
				for (auto x : LinkedInv->Inventory) {
					UInvSlotWidget* islot = CreateWidget<UInvSlotWidget>(pc, BP_InvSlot);
					islot->item = x;
					islot->inv = this;
					InvPanel->AddChild(islot);
				}
				
			}

		}
	}
}