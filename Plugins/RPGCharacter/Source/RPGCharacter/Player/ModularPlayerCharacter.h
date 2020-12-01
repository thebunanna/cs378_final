// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Equipment/ArmorTypes.h"
#include "../Equipment/Armor.h"
#include "../Equipment/WeaponTypes.h"
#include "../Equipment/Weapon.h"
#include "../Equipment/Shield.h"

#include "CharacterStates.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ModularPlayerCharacter.generated.h"

UCLASS()
class RPGCHARACTER_API AModularPlayerCharacter : public ACharacter
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
	AModularPlayerCharacter();

	void AttachMesh(FName, USkeletalMeshComponent*);

	UPROPERTY(Category = State, EditAnywhere, BlueprintReadWrite)
		ECharacterStateEnum CharacterState;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
		AWeapon* weapon;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
		AShield* shield;

	UPROPERTY(Category = State, EditAnywhere, BlueprintReadWrite)
		float MaxHP;

	UPROPERTY(Category = State, EditAnywhere, BlueprintReadWrite)
		float CurrentHP;

	/** Mesh Components */
	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Head;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Hair;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Eyebrows;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* FacialHair;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Torso;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftShoulder;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftUpperArm;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftLowerArm;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftHand;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* RightShoulder;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* RightUpperArm;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* RightLowerArm;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* RightHand;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Hips;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftKnee;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* LeftLeg;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* RightKnee;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* RightLeg;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Variables
	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		float MovementSpeed;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
		float CameraYRotation;

	UPROPERTY(Category = Camera, EditAnywhere, BlueprintReadWrite)
		float CameraXRotation;

	// Character state
	UFUNCTION(BlueprintCallable)
		bool CanPerformAction(ECharacterStateEnum updatedAction);

	UFUNCTION(BlueprintCallable)
		void UpdateActionState(ECharacterStateEnum newAction);

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
		void BlockBPEvent();

	UFUNCTION(BlueprintImplementableEvent)
		void BlockStopBPEvent();

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
		void Block();

	UFUNCTION(BlueprintCallable)
		void TakeCharDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Debugging
	// UFUNCTION(BlueprintCallable)
	// 	void LoadWeapon();

	// UFUNCTION(BlueprintCallable)
	// 	void LoadShield();
};
