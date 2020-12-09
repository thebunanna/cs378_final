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
    
    InputComponent->BindAction("PauseAction", IE_Pressed, this, &AModularPlayerController::Pause);
}

// ------------------
// Character Controls
// ------------------

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
void AModularPlayerController::Pause()
{
    AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
    if (character)
    {
        character->PauseEvent();
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
	ACharacter* character = this->GetCharacter();
	if (character)
	{
		if (character->IsA(AModularPlayerCharacter::StaticClass()))
		{
			AModularPlayerCharacter* ModularCharacter = Cast<AModularPlayerCharacter>(character);
			if (ModularCharacter)
			{
				ModularCharacter->CameraXBPEvent(value);
			}
		}
		else if (character->IsA(ACharacterCreator::StaticClass()))
		{
			ACharacterCreator* CreateCharacter = Cast<ACharacterCreator>(character);
			if (CreateCharacter)
			{
				CreateCharacter->RotateFace(value);
			}
		}
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

void AModularPlayerController::EquipArmor(TSubclassOf<AArmor> armor)
{
	AModularPlayerCharacter* character = Cast<AModularPlayerCharacter>(this->GetCharacter());
	if (character)
	{
		character->EquipArmor(armor);
	}
}

void AModularPlayerController::Save()
{
	ACharacter* character = this->GetCharacter();
	if (character)
	{
		if (character->IsA(AModularPlayerCharacter::StaticClass()))
		{
			AModularPlayerCharacter* ModularCharacter = Cast<AModularPlayerCharacter>(character);
			if (ModularCharacter)
			{
				ModularCharacter->SaveBPEvent();
			}
		}
		else if (character->IsA(ACharacterCreator::StaticClass()))
		{
			ACharacterCreator* CreateCharacter = Cast<ACharacterCreator>(character);
			if (CreateCharacter)
			{
				CreateCharacter->Save();
			}
		}
	}
}

// ---------------------------
// Character Creation Controls
// ---------------------------

void AModularPlayerController::ChangeGender(bool gender)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->ChangeGender(gender);
	}
}

void AModularPlayerController::ChangeHair(float value)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->ChangeHair(value);
	}
}

void AModularPlayerController::ChangeHead(float value)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->ChangeHead(value);
	}
}

void AModularPlayerController::ChangeEyebrows(float value)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->ChangeEyebrows(value);
	}
}

void AModularPlayerController::ChangeFacialHair(float value)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->ChangeFacialHair(value);
	}
}

void AModularPlayerController::SkinColor(float r, float g, float b)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->SkinColor(r, g, b);
	}
}

void AModularPlayerController::PaintColor(float r, float g, float b)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->PaintColor(r, g, b);
	}
}

void AModularPlayerController::HairColor(float r, float g, float b)
{
	ACharacterCreator* character = Cast<ACharacterCreator>(this->GetCharacter());
	if (character)
	{
		character->HairColor(r, g, b);
	}
}
