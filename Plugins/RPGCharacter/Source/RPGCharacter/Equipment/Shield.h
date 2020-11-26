// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponTypes.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

UCLASS()
class RPGCHARACTER_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

	UPROPERTY(Category = Shield, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* ShieldMesh;

	UPROPERTY(Category = Shield, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EWeaponTypeEnum WeaponType;

	UPROPERTY(Category = Shield, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Defense;
};
