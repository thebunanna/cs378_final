// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../Equipment/ArmorTypes.h"
#include "../Equipment/Armor.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProceduralEnemy.generated.h"

USTRUCT()
struct FArmorSet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<EArmorPartEnum, TSubclassOf<AArmor>> ArmorSet;
};

UCLASS()
class RPGCHARACTER_API AProceduralEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProceduralEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TMap<EArmorPartEnum, AArmor*> EquippedArmor;

	UPROPERTY(Category = ArmorType, EditAnywhere)
		TMap<FName, FArmorSet> ArmorSets;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		bool Gender;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> HeadOptions_Female;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> HeadOptions_Male;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Head;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> HairOptions;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Hair;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> EyebrowsOptions_Female;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> EyebrowsOptions_Male;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Eyebrows;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> FacialHairOptions;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* FacialHair;

	UFUNCTION(BlueprintCallable)
		void GenerateEnemy();

	UFUNCTION(BlueprintCallable)
		void EquipArmor(TSubclassOf<AArmor> armorReference);
};
