// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Weapons/WeaponOld.h"
#include <RPGCharacter/Player/ModularPlayerCharacter.h>
#include "DrawDebugHelpers.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterActionStateEnum : uint8
{
	IDLE UMETA(DisplayName = "Idling"),
	MOVE UMETA(DisplayName = "Moving"),
	ATTACK UMETA(DisplayName = "Attacking")
};

UENUM(BlueprintType)
enum class ECharacterWeaponEnum : uint8
{
	UNARMED UMETA(DisplayName = "Unarmed"),
	SWORD UMETA(DisplayName = "Sword")
};

UENUM(BlueprintType)
enum class ECharacterDirectionEnum : uint8
{
	FORWARD UMETA(DisplayName = "Forward"),
	FORWARD_RIGHT UMETA(DisplayName = "Forward Right"),
	RIGHT UMETA(DisplayName = "Forward"),
	BACKWARD_RIGHT UMETA(DisplayName = "Forward"),
	BACKWARD UMETA(DisplayName = "Forward"),
	BACKWARD_LEFT UMETA(DisplayName = "Forward"),
	LEFT UMETA(DisplayName = "Forward"),
	FORWARD_LEFT UMETA(DisplayName = "Forward")
};

UCLASS()
class CS378_FINAL_API APlayerCharacter : public AModularPlayerCharacter
{
	GENERATED_BODY()

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inv, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle_CheckInteract;

public:	
	/** Function to check for the closest Interactable in sight and in range. */
	UFUNCTION(BlueprintCallable)
	void CheckForInteractables();

	virtual void Tick(float DeltaSeconds) override;

};
