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
	AttachMesh("Head", Head);
	AttachMesh("Hair", Hair);
	AttachMesh("Eyebrowa", Eyebrows);
	AttachMesh("FacialHair", FacialHair);

	// Body Meshes
	AttachMesh("Torso", Torso);
	AttachMesh("LeftShoulder", LeftShoulder);
	AttachMesh("LeftUpperArm", LeftUpperArm);
	AttachMesh("LeftLowerARm", LeftLowerArm);
	AttachMesh("LeftHand", LeftHand);
	AttachMesh("RightShoulder", RightShoulder);
	AttachMesh("RightUpperArm", RightUpperArm);
	AttachMesh("RightLowerArm", RightLowerArm);
	AttachMesh("RightHand", RightHand);
	AttachMesh("Hips", Hips);
	AttachMesh("LeftKnee", LeftKnee);
	AttachMesh("LeftLeg", LeftLeg);
	AttachMesh("RightKnee", RightKnee);
	AttachMesh("RightLeg", RightLeg);

	// GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AModularPlayerCharacter::TakeDamage);

	// Variables
	MaxHP = 100.f;
	CurrentHP = 100.f;

	MovementSpeed = 1.f;
	CameraYRotation = 0.f;
	CameraXRotation = 0.f;

	CharacterState = ECharacterStateEnum::IDLE;
	// EquippedWeaponType = EWeaponTypeEnum::UNARMED;

}

void AModularPlayerCharacter::AttachMesh(FName Name, USkeletalMeshComponent* NewMesh)
{
	NewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(Name);
	NewMesh->SetupAttachment(GetMesh());
	NewMesh->SetMasterPoseComponent(GetMesh());
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