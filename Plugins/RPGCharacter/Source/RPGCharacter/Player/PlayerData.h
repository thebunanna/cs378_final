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
		TMap<EArmorPartEnum, FString> SavedArmor;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		bool Gender;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		int Hair;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		int Head;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		int Eyebrows;

	UPROPERTY(Category = Customization, EditAnywhere, BlueprintReadWrite)
		int FacialHair;
};