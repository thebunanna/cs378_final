// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponTypes.h"

#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class RPGCHARACTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionComponent;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EWeaponTypeEnum WeaponType;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Damage;
};
