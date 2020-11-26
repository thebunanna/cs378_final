// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularPlayerController.h"

AModularPlayerController::AModularPlayerController()
{
}

void AModularPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Forward", this, &AModularPlayerController::Forward);
	InputComponent->BindAxis("Right", this, &AModularPlayerController::Right);
	InputComponent->BindAxis("CameraY", this, &AModularPlayerController::CameraY);
	InputComponent->BindAxis("CameraX", this, &AModularPlayerController::CameraX);

	InputComponent->BindAction("AttackAction", IE_Pressed, this, &AModularPlayerController::Attack);
	InputComponent->BindAction("BlockAction", IE_Pressed, this, &AModularPlayerController::Block);
	InputComponent->BindAction("BlockAction", IE_Released, this, &AModularPlayerController::StopBlock);
}

void AModularPlayerController::Forward(float value)
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->ForwardBPEvent(value);
	}
}

void AModularPlayerController::Right(float value)
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->RightBPEvent(value);
	}
}

void AModularPlayerController::CameraY(float value)
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->CameraYBPEvent(value);
	}
}

void AModularPlayerController::CameraX(float value)
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->CameraXBPEvent(value);
	}
}

void AModularPlayerController::Attack()
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->AttackBPEvent();
	}
}

void AModularPlayerController::Block()
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->BlockBPEvent();
	}
}

void AModularPlayerController::StopBlock()
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->BlockStopBPEvent();
	}
}