// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor.h"

// Sets default values
AArmor::AArmor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	FemaleArmorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FemaleArmorMesh"));
	FemaleArmorMesh->SetupAttachment(RootComponent);

	FemaleArmorMesh->AddRelativeLocation(FVector(0, 0, -88));
	FemaleArmorMesh->AddLocalRotation(FQuat(FRotator(0, -90, 0)));

	MaleArmorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MaleArmorMesh"));
	MaleArmorMesh->SetupAttachment(RootComponent);

	MaleArmorMesh->AddRelativeLocation(FVector(0, 0, -88));
	MaleArmorMesh->AddLocalRotation(FQuat(FRotator(0, -90, 0)));
	MaleArmorMesh->SetVisibility(false);
}

void AArmor::SetGender(bool gender)
{
	if (gender)
	{
		MaleArmorMesh->SetVisibility(true);
		FemaleArmorMesh->SetVisibility(false);
	}
	else
	{
		MaleArmorMesh->SetVisibility(false);
		FemaleArmorMesh->SetVisibility(true);
	}
}