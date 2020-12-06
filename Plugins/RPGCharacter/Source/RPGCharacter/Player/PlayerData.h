// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Equipment/Armor.h"
#include "../Equipment/ArmorTypes.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class RPGCHARACTER_API UPlayerData : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPlayerData();

	UPROPERTY(Category = Armor, EditAnywhere, BlueprintReadWrite)
		TMap<EArmorPartEnum, TSubclassOf<AArmor>> SavedArmor;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		bool Gender;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* HairMesh;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* HeadMesh;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EyebrowsMesh;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* FacialHairMesh;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		UMaterialInstanceDynamic* Material;
};