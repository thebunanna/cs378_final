// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerData.h"

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

/**
 * 
 */
UCLASS()
class RPGCHARACTER_API USaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Armor, EditAnywhere, BlueprintReadWrite)
		TMap<EArmorPartEnum, TSubclassOf<AArmor>> SavedArmor;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		FString Name;

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
		FVector SkinColor;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		FVector PaintColor;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		FVector HairColor;
};
