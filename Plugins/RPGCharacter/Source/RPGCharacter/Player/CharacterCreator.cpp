// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreator.h"

// Sets default values
ACharacterCreator::ACharacterCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	// Attach Components
	Head = CreateDefaultSubobject<USkeletalMeshComponent>("Head");
	Head->SetupAttachment(GetMesh());
	Head->SetSkeletalMesh(HeadOptions_Female[0]);

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>("Hair");
	Hair->SetupAttachment(Head);
	Hair->SetSkeletalMesh(HairOptions[0]);

	Eyebrows = CreateDefaultSubobject<USkeletalMeshComponent>("Eyebrows");
	Eyebrows->SetupAttachment(Head);
	Eyebrows->SetSkeletalMesh(EyebrowsOptions_Female[0]);

	FacialHair = CreateDefaultSubobject<USkeletalMeshComponent>("FacialHair");
	FacialHair->SetupAttachment(Head);
	FacialHair->SetSkeletalMesh(FacialHairOptions[0]);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 60.f;
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->SetWorldLocation(this->GetActorLocation());

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ACharacterCreator::BeginPlay()
{
	Super::BeginPlay();

	data = (UPlayerData*) GetGameInstance();

	material = UMaterialInstanceDynamic::Create(Head->GetMaterial(0), NULL);
	// material->SetVectorParameterValue(FName(TEXT("Color_BodyArt")), FLinearColor(1.f, 0.f, 0.f));

	Head->SetMaterial(0, material);
	Hair->SetMaterial(0, material);
	Eyebrows->SetMaterial(0, material);
	FacialHair->SetMaterial(0, material);
}

void ACharacterCreator::ChangeGender(bool NewGender)
{
	Gender = NewGender;
	ChangeHead(HeadIndex);
	ChangeEyebrows(EyebrowsIndex);
}

void ACharacterCreator::ChangeHead(int value)
{
	if (Gender)
	{
		Head->SetSkeletalMesh(HeadOptions_Male[value]);
	}
	else
	{
		Head->SetSkeletalMesh(HeadOptions_Female[value]);
	}
}


void ACharacterCreator::ChangeHair(int value)
{
	Hair->SetSkeletalMesh(HairOptions[value]);
}

void ACharacterCreator::ChangeEyebrows(int value)
{
	if (Gender)
	{
		Eyebrows->SetSkeletalMesh(EyebrowsOptions_Male[value]);
	}
	else
	{
		Eyebrows->SetSkeletalMesh(EyebrowsOptions_Female[value]);
	}
}

void ACharacterCreator::ChangeFacialHair(int value)
{
	FacialHair->SetSkeletalMesh(FacialHairOptions[value]);
}

void ACharacterCreator::RotateFace(float value)
{
	Head->AddLocalRotation(FRotator(0.f, -value, 0.f));
}

void ACharacterCreator::SkinColor(float r, float g, float b)
{
	data->SkinColor = FVector(r, g, b);
	material->SetVectorParameterValue(FName(TEXT("Color_Skin")), FLinearColor(r, g, b));
}

void ACharacterCreator::PaintColor(float r, float g, float b)
{
	data->PaintColor = FVector(r, g, b);
	material->SetVectorParameterValue(FName(TEXT("Color_BodyArt")), FLinearColor(r, g, b));
}

void ACharacterCreator::HairColor(float r, float g, float b)
{
	data->HairColor = FVector(r, g, b);
	material->SetVectorParameterValue(FName(TEXT("Color_Hair")), FLinearColor(r, g, b));
}

void ACharacterCreator::Save()
{
	data->Gender = Gender;
	data->HairMesh = Hair->SkeletalMesh;
	data->HeadMesh = Head->SkeletalMesh;
	data->EyebrowsMesh = Eyebrows->SkeletalMesh;
	data->FacialHairMesh = FacialHair->SkeletalMesh;
	data->Material = material;
}