// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"
#include "../../Player//cs378_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../InventoryComponent.h"
#include "../InteractableBase.h"

FString UInGameWidget::GetText() 
{
	APlayerController *Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (Controller != NULL) {
		Acs378_PlayerController *pc =  Cast<Acs378_PlayerController>(Controller);
		if (pc == NULL) {
			UE_LOG(LogTemp, Warning, TEXT("non valid pc for inventory"));
		}
		else {
			UInventoryComponent* IController = pc->GetInventory();
			if (IController && IController->CurrentInteractable)
				return IController->CurrentInteractable->GetInteractText();
		}
		
	}
	return TEXT ("");

}