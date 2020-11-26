// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArmorTypes.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Armor.generated.h"

UCLASS()
class RPGCHARACTER_API AArmor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmor();

	UPROPERTY(Category = Armor, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* ArmorMesh;

	UPROPERTY(Category = Armor, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EArmorPartEnum ArmorPart;

	UPROPERTY(Category = Armor, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int Defense;
};
