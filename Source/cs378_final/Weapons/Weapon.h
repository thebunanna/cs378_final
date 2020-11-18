// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CS378_FINAL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* WeaponCollision;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite)
	float Durability;
};
