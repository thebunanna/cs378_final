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
	else if (InMouseEvent.IsMouseButtonDown(FKey(TEXT("LeftMouseButton")))) {
		UseFromInv();
	}
	return FReply::Handled();
}

FInventoryItem UInvSlotWidget::RemoveFromInv()
{
	UInventoryComponent* Inventory = GetInv();
	if (Inventory == NULL)
		return FInventoryItem();
	//if (GEngine) GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::White,
	//	FString::FormatAsNumber(item.UID));
	Inventory->RemoveFromInventory(item, true);


	ForceReload();

	return item;
}

FInventoryItem UInvSlotWidget::UseFromInv()
{
	UInventoryComponent* Inventory = GetInv();
	if (Inventory == NULL)
		return FInventoryItem();

	Inventory->UseItem(item);
	ForceReload();

	return item;
}

UInventoryComponent* UInvSlotWidget::GetInv()
{
	UInventoryWidget* IW = inv;

	if (IW == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Inventory Not Existing!"));
		return NULL;
	}

	UInventoryComponent* Inventory = IW->LinkedInv;//Cast<UInventoryComponent>(IW->LinkedInv.Get());
	if (Inventory == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("bp not set for this inv slot!"));
		return NULL;
	}
	return Inventory;
}

void UInvSlotWidget::ForceReload()
{
	UInventoryWidget* IW = inv;

	if (IW == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Inventory Not Existing!"));
		return;
	}

	IW->LoadInventory();
}