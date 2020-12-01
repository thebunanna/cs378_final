// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularPlayerCharacter.h"

// Sets default values
AModularPlayerCharacter::AModularPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->SetWorldLocation(this->GetActorLocation());

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Head Meshes
	Head = CreateDefaultSubobject<USkeletalMeshComponent>("Head");
	Head->SetupAttachment(GetMesh());
	Head->SetMasterPoseComponent(GetMesh());

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>("Hair");
	Hair->SetupAttachment(GetMesh());
	Hair->SetMasterPoseComponent(GetMesh());

	Eyebrows = CreateDefaultSubobject<USkeletalMeshComponent>("Eyebrows");
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->SetMasterPoseComponent(GetMesh());

	FacialHair = CreateDefaultSubobject<USkeletalMeshComponent>("FacialHair");
	FacialHair->SetupAttachment(GetMesh());
	FacialHair->SetMasterPoseComponent(GetMesh());

	// GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AModularPlayerCharacter::TakeDamage);

	// Variables
	MaxHP = 100.f;
	CurrentHP = 100.f;

	MovementSpeed = 1.f;
	CameraYRotation = 0.f;
	CameraXRotation = 0.f;

	CharacterState = ECharacterStateEnum::IDLE;
	gender = false;
	Hair_Option = 0;
	Head_Option = 0;
	Eyebrows_Option = 0;
	FacialHair_Option = 0;
}

// Called when the game starts or when spawned
void AModularPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool AModularPlayerCharacter::CanPerformAction(ECharacterStateEnum updatedAction)
{
	switch (updatedAction)
	{
	case ECharacterStateEnum::IDLE:
		return true;
	case ECharacterStateEnum::MOVE:
		if (CharacterState == ECharacterStateEnum::ATTACK || CharacterState == ECharacterStateEnum::BLOCK || CharacterState == ECharacterStateEnum::DEAD)
			return false;
		return true;
	case ECharacterStateEnum::ATTACK:
		return true;
	case ECharacterStateEnum::BLOCK:
		if (CharacterState == ECharacterStateEnum::ATTACK)
			return false;
		return true;
	case ECharacterStateEnum::DEAD:
		return true;
	}
	return true;
}

void AModularPlayerCharacter::UpdateActionState(ECharacterStateEnum newAction)
{
	CharacterState = newAction;
}

void AModularPlayerCharacter::Forward(float value)
{
	FVector dir = CameraBoom->GetForwardVector() * FVector(1, 1, 0);
	dir.Normalize();

	AddMovementInput(dir, value * MovementSpeed, true);
}

void AModularPlayerCharacter::Right(float value)
{
	FVector dir = CameraBoom->GetRightVector() * FVector(1, 1, 0);
	dir.Normalize();

	AddMovementInput(CameraBoom->GetRightVector() * FVector(1, 1, 0), value * MovementSpeed, true);
}

void AModularPlayerCharacter::CameraY(float value)
{
	CameraYRotation += value;
	CameraYRotation = FMath::Clamp(CameraYRotation, -70.f, 70.f);
	CameraBoom->SetWorldRotation(FQuat(FRotator(CameraYRotation, CameraXRotation, 0.f)));
}

void AModularPlayerCharacter::CameraX(float value)
{
	CameraXRotation += value;
	CameraBoom->SetWorldRotation(FQuat(FRotator(CameraYRotation, CameraXRotation - 90.f, 0.f)));
}

void AModularPlayerCharacter::Attack()
{

}

void AModularPlayerCharacter::Block()
{

}

void AModularPlayerCharacter::TakeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AWeapon::StaticClass()))
	{
		AWeapon* otherWeapon = (AWeapon*)OtherActor;

		if (weapon != otherWeapon)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Take damage!"));
			CurrentHP -= weapon->Damage;

			if (CurrentHP <= 0) {
				CharacterState = ECharacterStateEnum::DEAD;
			}
		}
	}
}


// ------------------
// Character Creation
// ------------------

void AModularPlayerCharacter::EquipArmor(AArmor* armorPiece)
{
	if (armorPiece)
	{
		if (EquippedArmor.Contains(armorPiece->ArmorPart))
		{
			EquippedArmor[armorPiece->ArmorPart]->Destroy();
			EquippedArmor.Remove(armorPiece->ArmorPart);
		}

		EquippedArmor.Add(armorPiece->ArmorPart, armorPiece);
		armorPiece->MaleArmorMesh->SetMasterPoseComponent(GetMesh());
		armorPiece->FemaleArmorMesh->SetMasterPoseComponent(GetMesh());
		armorPiece->SetGender(gender);

		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		armorPiece->AttachToActor(this, rules, "Root");
	}
}

void AModularPlayerCharacter::ChangeGender(bool NewGender)
{
	gender = NewGender;

	for (auto& armor : EquippedArmor)
	{
		if (armor.Value)
		{
			armor.Value->SetGender(gender);
		}
	}

	ChangeHead(Head_Option);
}

void AModularPlayerCharacter::ChangeHead(float value)
{
	int index = (int) value;
	int digit1 = index / 10;
	int digit2 = index % 10;

	Head_Option = index;

	FString number = FString::FromInt(digit1) + FString::FromInt(digit2);
	FString Gender = gender ? "Male" : "Female";
	FString reference = FString("SkeletalMesh'/Game/ModularCharacters/ModularParts/SK_Chr_Head_" + Gender +"_" + number + ".SK_Chr_Head_" + Gender + "_" + number + "'");
	ChangePart(Head, reference);
}


void AModularPlayerCharacter::ChangeHair(float value)
{
	if (value == 0)
	{
		Hair->SetSkeletalMesh(NULL);
		return;
	}
	int index = (int)value;
	int digit1 = index / 10;
	int digit2 = index % 10;

	Hair_Option = index;

	FString number = FString::FromInt(digit1) + FString::FromInt(digit2);
	FString reference = FString("SkeletalMesh'/Game/ModularCharacters/ModularParts/SK_Chr_Hair_" + number + ".SK_Chr_Hair_" + number + "'");
	ChangePart(Hair, reference);
}

void AModularPlayerCharacter::ChangeEyebrows(float value)
{
	if (value == 0)
	{
		Eyebrows->SetSkeletalMesh(NULL);
		return;
	}
	int index = (int)value;
	int digit1 = index / 10;
	int digit2 = index % 10;

	Eyebrows_Option = index;

	FString number = FString::FromInt(digit1) + FString::FromInt(digit2);
	FString Gender = gender ? "Male" : "Female";
	FString reference = FString("SkeletalMesh'/Game/ModularCharacters/ModularParts/SK_Chr_Eyebrow_" + Gender + "_" + number + ".SK_Chr_Eyebrow_" + Gender + "_" + number + "'");
	ChangePart(Eyebrows, reference);
}

void AModularPlayerCharacter::ChangeFacialHair(float value)
{
	if (value == 0)
	{
		FacialHair->SetSkeletalMesh(NULL);
		return;
	}
	int index = (int)value;
	int digit1 = index / 10;
	int digit2 = index % 10;

	FacialHair_Option = index;

	FString number = FString::FromInt(digit1) + FString::FromInt(digit2);
	FString reference = FString("SkeletalMesh'/Game/ModularCharacters/ModularParts/SK_Chr_FacialHair_Male_" + number + ".SK_Chr_FacialHair_Male_" + number + "'");
	ChangePart(FacialHair, reference);
}

void AModularPlayerCharacter::ChangePart(USkeletalMeshComponent* headPart, FString refrence)
{
	USkeletalMesh* NewMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(refrence)));

	if (!NewMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	headPart->SetSkeletalMesh(NewMesh);
}

// ---------
// Save Data
// ---------

void AModularPlayerCharacter::Save()
{
	UPlayerData* data = (UPlayerData*) GetGameInstance();

	if (data->IsA(UPlayerData::StaticClass()))
	{
		for (auto& armor : EquippedArmor)
		{
			if (armor.Value)
			{
				if (data->SavedArmor.Contains(armor.Key))
					data->SavedArmor.Remove(armor.Key);
				
				data->SavedArmor.Add(armor.Key, armor.Value->GetClass()->GetPathName());
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("My class is: %s"), *data->SavedArmor[armor.Key].ToString()));
			}
		}
	}

	data->Hair = Hair_Option;
	data->Head = Head_Option;
	data->Eyebrows = Eyebrows_Option;
	data->FacialHair = FacialHair_Option;
}

void AModularPlayerCharacter::Load()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UPlayerData* data = (UPlayerData*) GetGameInstance();

	if (data->IsA(UPlayerData::StaticClass()))
	{
		TMap<EArmorPartEnum, FString> SavedArmor = data->SavedArmor;

		for (auto& armor : SavedArmor)
		{
			// FString ClassName = armor.Value;
			UObject* SpawnArmor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, *FString(FString("Blueprint'" + data->SavedArmor[armor.Key] + "'"))));

			UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnArmor);
			if (!SpawnArmor || !GeneratedBP)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			}
			else
			{
				AArmor* armorPiece = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
				EquipArmor(armorPiece);
			}

			// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My class is: %s"), *FString(SpawnActor)));
		}
	}

	ChangeHair(data->Hair);
	ChangeHead(data->Head);
	ChangeEyebrows(data->Eyebrows);
	ChangeFacialHair(data->FacialHair);
}




























// -----
// Debug
// -----

void AModularPlayerCharacter::EquipNoneArmor()
{
	// Equip Torso
	UObject* SpawnTorso = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneTorso_BP.NoneTorso_BP'")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnTorso);
	if (!SpawnTorso)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

	AArmor* armor = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip Hips
	UObject* SpawnHips = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneHips_BP.NoneHips_BP'")));

	UBlueprint* GeneratedHipsBP = Cast<UBlueprint>(SpawnHips);
	if (!SpawnHips)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedHipsBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftUpperArm
	UObject* SpawnLeftUpperArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneLeftUpperArm_BP.NoneLeftUpperArm_BP'")));

	UBlueprint* GeneratedLeftUpperArmBP = Cast<UBlueprint>(SpawnLeftUpperArm);
	if (!SpawnLeftUpperArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedLeftUpperArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightUpperArm
	UObject* SpawnRightUpperArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneRightUpperArm_BP.NoneRightUpperArm_BP'")));

	UBlueprint* GeneratedRightUpperArmBP = Cast<UBlueprint>(SpawnRightUpperArm);
	if (!SpawnRightUpperArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedRightUpperArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftLowerArm
	UObject* SpawnLeftLowerArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneLeftLowerArm_BP.NoneLeftLowerArm_BP'")));

	UBlueprint* GeneratedLeftLowerArmBP = Cast<UBlueprint>(SpawnLeftLowerArm);
	if (!SpawnLeftLowerArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedLeftLowerArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightLowerArm
	UObject* SpawnRightLowerArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneRightLowerArm_BP.NoneRightLowerArm_BP'")));

	UBlueprint* GeneratedRightLowerArmBP = Cast<UBlueprint>(SpawnRightLowerArm);
	if (!SpawnRightLowerArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*) GetWorld()->SpawnActor<AActor>(GeneratedRightLowerArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftHand
	UObject* SpawnLeftHand = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneLeftHand_BP.NoneLeftHand_BP'")));

	UBlueprint* GeneratedLeftHandBP = Cast<UBlueprint>(SpawnLeftHand);
	if (!SpawnLeftHand)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftHandBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightHand
	UObject* SpawnRightHand = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneRightHand_BP.NoneRightHand_BP'")));

	UBlueprint* GeneratedRightHandBP = Cast<UBlueprint>(SpawnRightHand);
	if (!GeneratedRightHandBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightHandBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftLeg
	UObject* SpawnLeftLeg = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneLeftLeg_BP.NoneLeftLeg_BP'")));

	UBlueprint* GeneratedLeftLegBP = Cast<UBlueprint>(SpawnLeftLeg);
	if (!GeneratedLeftLegBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftLegBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightLeg
	UObject* SpawnRightLeg = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/NoneRightLeg_BP.NoneRightLeg_BP'")));

	UBlueprint* GeneratedRightLegBP = Cast<UBlueprint>(SpawnRightLeg);
	if (!GeneratedRightLegBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightLegBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);
}

void AModularPlayerCharacter::EquipLightArmor()
{
		// Equip Torso
		UObject* SpawnTorso = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightTorso_BP.LightTorso_BP'")));

		UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnTorso);
		if (!SpawnTorso)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

		AArmor* armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip Hips
		UObject* SpawnHips = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightHips_BP.LightHips_BP'")));

		UBlueprint* GeneratedHipsBP = Cast<UBlueprint>(SpawnHips);
		if (!SpawnHips)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedHipsBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip LeftUpperArm
		UObject* SpawnLeftUpperArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightLeftUpperArm_BP.LightLeftUpperArm_BP'")));

		UBlueprint* GeneratedLeftUpperArmBP = Cast<UBlueprint>(SpawnLeftUpperArm);
		if (!SpawnLeftUpperArm)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftUpperArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip RightUpperArm
		UObject* SpawnRightUpperArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightRightUpperArm_BP.LightRightUpperArm_BP'")));

		UBlueprint* GeneratedRightUpperArmBP = Cast<UBlueprint>(SpawnRightUpperArm);
		if (!SpawnRightUpperArm)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightUpperArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip LeftLowerArm
		UObject* SpawnLeftLowerArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightLeftLowerArm_BP.LightLeftLowerArm_BP'")));

		UBlueprint* GeneratedLeftLowerArmBP = Cast<UBlueprint>(SpawnLeftLowerArm);
		if (!SpawnLeftLowerArm)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftLowerArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip RightLowerArm
		UObject* SpawnRightLowerArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightRightLowerArm_BP.LightRightLowerArm_BP'")));

		UBlueprint* GeneratedRightLowerArmBP = Cast<UBlueprint>(SpawnRightLowerArm);
		if (!SpawnRightLowerArm)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightLowerArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip LeftHand
		UObject* SpawnLeftHand = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightLeftHand_BP.LightLeftHand_BP'")));

		UBlueprint* GeneratedLeftHandBP = Cast<UBlueprint>(SpawnLeftHand);
		if (!SpawnLeftHand)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftHandBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip RightHand
		UObject* SpawnRightHand = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightRightHand_BP.LightRightHand_BP'")));

		UBlueprint* GeneratedRightHandBP = Cast<UBlueprint>(SpawnRightHand);
		if (!GeneratedRightHandBP)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightHandBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip LeftLeg
		UObject* SpawnLeftLeg = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightLeftLeg_BP.LightLeftLeg_BP'")));

		UBlueprint* GeneratedLeftLegBP = Cast<UBlueprint>(SpawnLeftLeg);
		if (!GeneratedLeftLegBP)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftLegBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		// Equip RightLeg
		UObject* SpawnRightLeg = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/LightRightLeg_BP.LightRightLeg_BP'")));

		UBlueprint* GeneratedRightLegBP = Cast<UBlueprint>(SpawnRightLeg);
		if (!GeneratedRightLegBP)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
			return;
		}

		armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightLegBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		EquipArmor(armor);

		LoadWeapon();
		LoadShield();
}

void AModularPlayerCharacter::EquipHeavyArmor()
{
	// Equip Torso
	UObject* SpawnTorso = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyTorso_BP.HeavyTorso_BP'")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnTorso);
	if (!SpawnTorso)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

	AArmor* armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip Hips
	UObject* SpawnHips = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyHips_BP.HeavyHips_BP'")));

	UBlueprint* GeneratedHipsBP = Cast<UBlueprint>(SpawnHips);
	if (!SpawnHips)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedHipsBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftUpperArm
	UObject* SpawnLeftUpperArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyLeftUpperArm_BP.HeavyLeftUpperArm_BP'")));

	UBlueprint* GeneratedLeftUpperArmBP = Cast<UBlueprint>(SpawnLeftUpperArm);
	if (!SpawnLeftUpperArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftUpperArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightUpperArm
	UObject* SpawnRightUpperArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyRightUpperArm_BP.HeavyRightUpperArm_BP'")));

	UBlueprint* GeneratedRightUpperArmBP = Cast<UBlueprint>(SpawnRightUpperArm);
	if (!SpawnRightUpperArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightUpperArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftLowerArm
	UObject* SpawnLeftLowerArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyLeftLowerArm_BP.HeavyLeftLowerArm_BP'")));

	UBlueprint* GeneratedLeftLowerArmBP = Cast<UBlueprint>(SpawnLeftLowerArm);
	if (!SpawnLeftLowerArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftLowerArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightLowerArm
	UObject* SpawnRightLowerArm = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyRightLowerArm_BP.HeavyRightLowerArm_BP'")));

	UBlueprint* GeneratedRightLowerArmBP = Cast<UBlueprint>(SpawnRightLowerArm);
	if (!SpawnRightLowerArm)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightLowerArmBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftHand
	UObject* SpawnLeftHand = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyLeftHand_BP.HeavyLeftHand_BP'")));

	UBlueprint* GeneratedLeftHandBP = Cast<UBlueprint>(SpawnLeftHand);
	if (!SpawnLeftHand)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftHandBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightHand
	UObject* SpawnRightHand = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyRightHand_BP.HeavyRightHand_BP'")));

	UBlueprint* GeneratedRightHandBP = Cast<UBlueprint>(SpawnRightHand);
	if (!GeneratedRightHandBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightHandBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip LeftLeg
	UObject* SpawnLeftLeg = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyLeftLeg_BP.HeavyLeftLeg_BP'")));

	UBlueprint* GeneratedLeftLegBP = Cast<UBlueprint>(SpawnLeftLeg);
	if (!GeneratedLeftLegBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedLeftLegBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	// Equip RightLeg
	UObject* SpawnRightLeg = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Armor/HeavyRightLeg_BP.HeavyRightLeg_BP'")));

	UBlueprint* GeneratedRightLegBP = Cast<UBlueprint>(SpawnRightLeg);
	if (!GeneratedRightLegBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	armor = (AArmor*)GetWorld()->SpawnActor<AActor>(GeneratedRightLegBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	EquipArmor(armor);

	if (shield)
	{
		shield->Destroy();
	}
	LoadWeapon2();
}


void AModularPlayerCharacter::LoadWeapon()
{
	if (weapon) {
		weapon->Destroy();
	}

	UObject* SpawnWeapon = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Weapons/StraightSword_BP.StraightSword_BP'")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnWeapon);
	if (!SpawnWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	UClass* SpawnClass = SpawnWeapon->StaticClass();
	if (SpawnClass == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}

	FVector position = FVector(0, 0, 0);
	FRotator rotator = FRotator(0, 0, 0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	weapon = GetWorld()->SpawnActor<AWeapon>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success!"));
	FName WeaponSocketR = TEXT("WeaponSocketR");
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	weapon->WeaponMesh->SetSimulatePhysics(false);
	weapon->SetActorEnableCollision(false);
	weapon->AttachToComponent(GetMesh(), rules, WeaponSocketR);
	weapon->Damage = 1000;
}

void AModularPlayerCharacter::LoadWeapon2()
{
	if (weapon) {
		weapon->Destroy();
	}

	UObject* SpawnWeapon = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Weapons/Greatsword_BP.Greatsword_BP'")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnWeapon);
	if (!SpawnWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	UClass* SpawnClass = SpawnWeapon->StaticClass();
	if (SpawnClass == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}

	FVector position = FVector(0, 0, 0);
	FRotator rotator = FRotator(0, 0, 0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	weapon = GetWorld()->SpawnActor<AWeapon>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success!"));
	FName WeaponSocketR = TEXT("WeaponSocketR");
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	weapon->WeaponMesh->SetSimulatePhysics(false);
	weapon->SetActorEnableCollision(false);
	weapon->AttachToComponent(GetMesh(), rules, WeaponSocketR);
	weapon->Damage = 1000;
}

void AModularPlayerCharacter::LoadShield()
{
	UObject* SpawnWeapon = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/Equipment/Weapons/LightShield_BP.LightShield_BP'")));

	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnWeapon);
	if (!SpawnWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		return;
	}

	UClass* SpawnClass = SpawnWeapon->StaticClass();
	if (SpawnClass == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
		return;
	}

	FVector position = FVector(0, 0, 0);
	FRotator rotator = FRotator(0, 0, 0);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	shield = (AShield*)GetWorld()->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success!"));
	FName WeaponSocketR = TEXT("ShieldSocketL");
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	shield->ShieldMesh->SetSimulatePhysics(false);
	shield->SetActorEnableCollision(false);
	shield->AttachToComponent(GetMesh(), rules, WeaponSocketR);
}
