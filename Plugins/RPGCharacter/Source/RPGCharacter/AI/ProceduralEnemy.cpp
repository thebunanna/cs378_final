// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralEnemy.h"

// Sets default values
AProceduralEnemy::AProceduralEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Load heads
	for (int i = 0; i < 23; ++i)
	{
		int digit1 = i / 10;
		int digit2 = i % 10;
		FString index = FString::FromInt(digit1) + FString::FromInt(digit2);

		
		FString MaleReference = FString("SkeletalMesh'/RPGCharacter/ModularCharacters/ModularParts/SK_Chr_Head_Male_" + index + ".SK_Chr_Head_Male_" + index + "'");
		USkeletalMesh* NewMaleMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(MaleReference)));
		HeadOptions_Male.Add(NewMaleMesh);

		FString FemaleReference = FString("SkeletalMesh'/RPGCharacter/ModularCharacters/ModularParts/SK_Chr_Head_Female_" + index + ".SK_Chr_Head_Female_" + index + "'");
		USkeletalMesh* NewFemaleMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(FemaleReference)));
		HeadOptions_Female.Add(NewFemaleMesh);
	}

	// Load hairs
	for (int i = 0; i < 39; ++i)
	{
		int digit1 = i / 10;
		int digit2 = i % 10;
		FString index = FString::FromInt(digit1) + FString::FromInt(digit2);

		FString Reference = FString("SkeletalMesh'/RPGCharacter/ModularCharacters/ModularParts/SK_Chr_Hair_" + index + ".SK_Chr_Hair_" + index + "'");
		USkeletalMesh* NewMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(Reference)));
		HairOptions.Add(NewMesh);
	}

	// Load eyebrows
	for (int i = 0; i < 8; ++i)
	{
		int digit1 = i / 10;
		int digit2 = i % 10;
		FString index = FString::FromInt(digit1) + FString::FromInt(digit2);

		FString MaleReference = FString("SkeletalMesh'/RPGCharacter/ModularCharacters/ModularParts/SK_Chr_Eyebrow_Male_" + index + ".SK_Chr_Eyebrow_Male_" + index + "'");
		USkeletalMesh* NewMaleMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(MaleReference)));
		EyebrowsOptions_Male.Add(NewMaleMesh);

		FString FemaleReference = FString("SkeletalMesh'/RPGCharacter/ModularCharacters/ModularParts/SK_Chr_Eyebrow_Female_" + index + ".SK_Chr_Eyebrow_Female_" + index + "'");
		USkeletalMesh* NewFemaleMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(FemaleReference)));
		EyebrowsOptions_Female.Add(NewFemaleMesh);
	}

	// Load hairs
	for (int i = 0; i < 19; ++i)
	{
		int digit1 = i / 10;
		int digit2 = i % 10;
		FString index = FString::FromInt(digit1) + FString::FromInt(digit2);

		FString Reference = FString("SkeletalMesh'/RPGCharacter/ModularCharacters/ModularParts/SK_Chr_FacialHair_Male_" + index + ".SK_Chr_FacialHair_Male_" + index + "'");
		USkeletalMesh* NewMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *FString(Reference)));
		FacialHairOptions.Add(NewMesh);
	}

	Head = CreateDefaultSubobject<USkeletalMeshComponent>("Head");
	Head->SetupAttachment(GetMesh());

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>("Hair");
	Hair->SetupAttachment(Head);

	Eyebrows = CreateDefaultSubobject<USkeletalMeshComponent>("Eyebrows");
	Eyebrows->SetupAttachment(Head);

	FacialHair = CreateDefaultSubobject<USkeletalMeshComponent>("FacialHair");
	FacialHair->SetupAttachment(Head);
}

// Called when the game starts or when spawned
void AProceduralEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProceduralEnemy::GenerateEnemy()
{
	Gender = FMath::RandRange(0, 1) == 0;

	// Generate Armor
	int index = FMath::RandRange(0, ArmorSets.Num() - 1);
	int i = 0;
	for (auto& ArmorSet : ArmorSets)
	{
		if (i == index)
		{
			for	(auto& Armor : ArmorSet.Value.ArmorSet)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AArmor* armorPiece = (AArmor*) GetWorld()->SpawnActor<AActor>(Armor.Value, GetActorLocation(), GetActorRotation(), SpawnParams);

				if (EquippedArmor.Contains(armorPiece->ArmorPart))
				{
					EquippedArmor[armorPiece->ArmorPart]->Destroy();
					EquippedArmor.Remove(armorPiece->ArmorPart);
				}

				EquippedArmor.Add(armorPiece->ArmorPart, armorPiece);
				armorPiece->MaleArmorMesh->SetMasterPoseComponent(GetMesh());
				armorPiece->FemaleArmorMesh->SetMasterPoseComponent(GetMesh());
				armorPiece->SetGender(Gender);

				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
				armorPiece->AttachToActor(this, rules, "Root");
			}
			break;
		}

		++i;
	}

	// Generate Face
	index = FMath::RandRange(0, HeadOptions_Male.Num() - 1);
	if (Gender)
	{
		Head->SetSkeletalMesh(HeadOptions_Male[index]);
	}
	else
	{
		Head->SetSkeletalMesh(HeadOptions_Female[index]);
	}
	
	Head->SetMasterPoseComponent(GetMesh());

	index = FMath::RandRange(0, HairOptions.Num() - 1);
	Hair->SetSkeletalMesh(HairOptions[index]);
	Hair->SetMasterPoseComponent(GetMesh());

	index = FMath::RandRange(0, EyebrowsOptions_Male.Num() - 1);
	Eyebrows->SetSkeletalMesh(EyebrowsOptions_Male[index]);
	Eyebrows->SetMasterPoseComponent(GetMesh());

	index = FMath::RandRange(0, FacialHairOptions.Num() - 1);
	if (Gender)
	{
		FacialHair->SetSkeletalMesh(FacialHairOptions[index]);
	}
	else
	{
		FacialHair->SetSkeletalMesh(nullptr);
	}
	FacialHair->SetMasterPoseComponent(GetMesh());

	// Generate Colors
	
}

void AProceduralEnemy::EquipArmor(TSubclassOf<AArmor> armorReference)
{

}