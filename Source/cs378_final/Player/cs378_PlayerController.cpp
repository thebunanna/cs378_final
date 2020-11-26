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
	InputComponent->BindAxis("Forward", this, &Acs378_PlayerController::Forward);
	InputComponent->BindAxis("Right", this, &Acs378_PlayerController::Right);
	InputComponent->BindAxis("CameraY", this, &Acs378_PlayerController::CameraY);
	InputComponent->BindAxis("CameraX", this, &Acs378_PlayerController::CameraX);

	InputComponent->BindAction("AttackAction", IE_Pressed, this, &Acs378_PlayerController::Attack);
	InputComponent->BindAction("InteractAction", IE_Pressed, this, &Acs378_PlayerController::Pickup);

	InputComponent->BindAction("Interact", IE_Pressed, Inv, &UInventoryComponent::Interact);
	//if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::White,
	//	           TEXT("HI there"));
}

void Acs378_PlayerController::Forward(float value)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->ForwardBPEvent(value);
	}
}

void Acs378_PlayerController::Right(float value)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->RightBPEvent(value);
	}
}

void Acs378_PlayerController::CameraY(float value)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->CameraYBPEvent(value);
	}
}

void Acs378_PlayerController::CameraX(float value)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->CameraXBPEvent(value);
	}
}

void Acs378_PlayerController::Attack()
{
	APlayerCharacter* character = Cast<APlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->AttackBPEvent();
	}
}

void Acs378_PlayerController::Pickup()
{
	APlayerCharacter* character = Cast<APlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->PickupBPEvent();
	}
}

UInventoryComponent* Acs378_PlayerController::GetInventory()
{
	return this->Inv;
}
