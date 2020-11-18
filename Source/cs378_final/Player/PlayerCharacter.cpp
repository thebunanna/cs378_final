// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->SetWorldLocation(this->GetActorLocation());

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Variables
	MovementSpeed = 1.f;
	CameraYRotation = 0.f;
	CameraXRotation = 0.f;

	isAttack = false;

	CharacterActionState = ECharacterActionStateEnum::IDLE;
	WeaponState = ECharacterWeaponEnum::SWORD;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool APlayerCharacter::CanPerformAction(ECharacterActionStateEnum updatedAction)
{
	switch (updatedAction)
	{
		case ECharacterActionStateEnum::IDLE:
			if (CharacterActionState == ECharacterActionStateEnum::ATTACK)
				return false;
			return true;
		case ECharacterActionStateEnum::MOVE:
			if (CharacterActionState == ECharacterActionStateEnum::ATTACK)
				return false;
			return true;
		case ECharacterActionStateEnum::ATTACK:
			return true;
	}
	return true;
}

void APlayerCharacter::UpdateActionState(ECharacterActionStateEnum newAction)
{
	CharacterActionState = newAction;
}

void APlayerCharacter::Forward(float value)
{
	FVector dir = CameraBoom->GetForwardVector() * FVector(1, 1, 0);
	dir.Normalize();

	AddMovementInput(dir, value * MovementSpeed, true);
}

void APlayerCharacter::Right(float value)
{
	FVector dir = CameraBoom->GetRightVector() * FVector(1, 1, 0);
	dir.Normalize();

	AddMovementInput(dir, value * MovementSpeed, true);
}

void APlayerCharacter::CameraY(float value)
{
	CameraYRotation += value;
	CameraYRotation = FMath::Clamp(CameraYRotation, -70.f, 70.f);
	CameraBoom->SetWorldRotation(FQuat(FRotator(CameraYRotation, CameraXRotation, 0.f)));
}

void APlayerCharacter::CameraX(float value)
{
	CameraXRotation += value;
	CameraBoom->SetWorldRotation(FQuat(FRotator(CameraYRotation, CameraXRotation - 90.f, 0.f)));
}

void APlayerCharacter::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("Attack")));
	isAttack = true;
}

void APlayerCharacter::Pickup()
{
	FHitResult Hit;
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * 150 - GetActorUpVector() * 90;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), start, end, FColor::Green, true, -1, 0, 1.f);
	GetWorld()->LineTraceSingleByChannel(Hit, start, end, ECollisionChannel::ECC_Visibility, CollisionParameters);

	AActor* actor = Hit.GetActor();
	if (actor && actor->IsA(AWeapon::StaticClass())) {
		AWeapon* pick = (AWeapon*) actor;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success!"));
		FName BackpackSocket = TEXT("WeaponSocket");
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

		pick->WeaponMesh->SetSimulatePhysics(false);
		actor->SetActorEnableCollision(false);
		actor->AttachToComponent(GetMesh(), rules, BackpackSocket);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Here!"));
	}

}