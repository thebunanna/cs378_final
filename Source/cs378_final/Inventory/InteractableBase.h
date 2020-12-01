// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class CS378_FINAL_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintNativeEvent)
		void Interact(APlayerController* Controller);
	virtual void Interact_Implementation(APlayerController* Controller);

	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		FString Action;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		FString GetInteractText() const;
};
