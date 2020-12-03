// Fill out your copyright notice in the Description page of Project Settings.


#include "cs378_PlayerController.h"
#include "../Inventory/InventoryComponent.h"
#include "UObject/ConstructorHelpers.h"

Acs378_PlayerController::Acs378_PlayerController()
{
	//static ConstructorHelpers::FObjectFinder<UInventoryComponent> InvBP = TEXT("InventoryComponent'/Game/Blueprints/InventoryComponent_BP.InventoryComponent_BP_C'");
	
	//if (InvBP.Succeeded()) {
	//	Inv = InvBP.Object;
		//Inv = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	//
	//else {
		//UE_LOG(LogTemp, Warning, TEXT("no inv component found"));
	Inv = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));		
	//}
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

void Acs378_PlayerController::LoadInvWidget()
{
	if (IW == NULL) {
		IW = CreateWidget<UInventoryWidget>(this, BP_InvWidget);
		IW->LinkedInv = Inv;
	}
}
