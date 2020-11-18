// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Weapons/Weapon.h"

#include "DrawDebugHelpers.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
class CS378_FINAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(Category = State, EditAnywhere, BlueprintReadWrite)
	ECharacterActionStateEnum CharacterActionState;

	UPROPERTY(Category = State, EditAnywhere, BlueprintReadWrite)
	ECharacterWeaponEnum WeaponState;

	// UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
	// AActor* weapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Variables
	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
	bool isAttack;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
	float CameraYRotation;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
	float CameraXRotation;

	// Character state
	UFUNCTION(BlueprintCallable)
	bool CanPerformAction(ECharacterActionStateEnum updatedAction);

	UFUNCTION(BlueprintCallable)
	void UpdateActionState(ECharacterActionStateEnum newAction);

	// Blueprint functions
	UFUNCTION(BlueprintImplementableEvent)
	void ForwardBPEvent(float value);

	UFUNCTION(BlueprintImplementableEvent)
	void RightBPEvent(float value);

	UFUNCTION(BlueprintImplementableEvent)
	void CameraYBPEvent(float value);

	UFUNCTION(BlueprintImplementableEvent)
	void CameraXBPEvent(float value);

	UFUNCTION(BlueprintImplementableEvent)
	void AttackBPEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void PickupBPEvent();

	// C++ Functions
	UFUNCTION(BlueprintCallable)
	void Forward(float value);

	UFUNCTION(BlueprintCallable)
	void Right(float value);

	UFUNCTION(BlueprintCallable)
	void CameraY(float value);

	UFUNCTION(BlueprintCallable)
	void CameraX(float value);

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void Pickup();
};
