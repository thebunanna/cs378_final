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

void AModularPlayerCharacter::TakeHPDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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


// -------------------
// Character Equipment
// -------------------

void AModularPlayerCharacter::EquipArmor(TSubclassOf<AArmor> armorReference)
{
	if (armorReference)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AArmor* armorPiece = (AArmor*) GetWorld()->SpawnActor<AActor>(armorReference, GetActorLocation(), GetActorRotation(), SpawnParams);

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

// // ---------
// // Save Data
// // ---------

void AModularPlayerCharacter::Save()
{
	UPlayerData* data = (UPlayerData*) GetGameInstance();

	if (data->IsA(UPlayerData::StaticClass()))
	{
		for (auto& armor : EquippedArmor)
		{
			data->SavedArmor.Add(armor.Key, DefaultArmor[armor.Key]);
		}
	}
}

void AModularPlayerCharacter::Load()
{
	UPlayerData* data = (UPlayerData*) GetGameInstance();

	if (data->IsA(UPlayerData::StaticClass()))
	{
		TMap<EArmorPartEnum, TSubclassOf<AArmor>> SavedArmor = data->SavedArmor;

		gender = data->Gender;

		Head->SetSkeletalMesh(data->HeadMesh);
		data->Material = UMaterialInstanceDynamic::Create(Head->GetMaterial(0), NULL);
		Head->SetMaterial(0, data->Material);

		Hair->SetSkeletalMesh(data->HairMesh);
		Hair->SetMaterial(0, data->Material);

		Eyebrows->SetSkeletalMesh(data->EyebrowsMesh);
		Eyebrows->SetMaterial(0, data->Material);

		FacialHair->SetSkeletalMesh(data->FacialHairMesh);
		FacialHair->SetMaterial(0, data->Material);

		data->Material->SetVectorParameterValue(FName(TEXT("Color_Skin")), FLinearColor(data->SkinColor));
		data->Material->SetVectorParameterValue(FName(TEXT("Color_BodyArt")), FLinearColor(data->PaintColor));
		data->Material->SetVectorParameterValue(FName(TEXT("Color_Hair")), FLinearColor(data->HairColor));

		for (auto& armor : SavedArmor)
		{
			if (armor.Value)
			{
				EquipArmor(armor.Value);
			}
			else
			{
				EquipArmor(DefaultArmor[armor.Key]);
			}
		}

		for (auto& armor : EquippedArmor)
		{
			if (armor.Value)
			{
				armor.Value->MaleArmorMesh->SetMaterial(0, data->Material);
				armor.Value->FemaleArmorMesh->SetMaterial(0, data->Material);
			}
			
		}
	}
}
