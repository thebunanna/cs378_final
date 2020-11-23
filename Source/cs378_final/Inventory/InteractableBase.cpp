// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Name = "Interactable";
	Action = "interact";

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableBase::Interact_Implementation(APlayerController* Controller)
{
	return;
}

FString AInteractableBase::GetInteractText() const
{
	return FString::Printf(TEXT("%s: Press F to %s"), *Name, *Action);
}

