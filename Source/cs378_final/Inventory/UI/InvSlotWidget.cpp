// Fill out your copyright notice in the Description page of Project Settings.


#include "InvSlotWidget.h"
#include "Input/Events.h"
#include "Layout/Geometry.h"
#include "InputCoreTypes.h"
#include "../../Player//cs378_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../InventoryComponent.h"

FReply UInvSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	
	FKey key = InMouseEvent.GetEffectingButton();
	if (InMouseEvent.IsMouseButtonDown(FKey(TEXT("RightMouseButton")))) {
		if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::White,
			TEXT("Mouse Clicked!"));

		RemoveFromInv();
	}
	return FReply::Handled();
}

FInventoryItem UInvSlotWidget::RemoveFromInv()
{
	UInventoryWidget* IW = inv;

	if (IW == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Inventory Not Existing!"));
		return FInventoryItem();
	}

	UInventoryComponent* Inventory = IW->LinkedInv;//Cast<UInventoryComponent>(IW->LinkedInv.Get());
	if (Inventory == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("bp not set for this inv slot!"));
		return FInventoryItem();
	}
	//if (GEngine) GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::White,
	//	FString::FormatAsNumber(item.UID));
	Inventory->Inventory.Remove(item);

	IW->LoadInventory();

	return item;
}
