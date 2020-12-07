// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "InteractableBase.generated.h"

UINTERFACE()
class CS378_FINAL_API UInteractableBase : public UInterface
{
	GENERATED_BODY()

};


class CS378_FINAL_API IInteractableBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

public:

	UFUNCTION(BlueprintNativeEvent)
		void Interact(APlayerController* Controller);

	virtual void Interact_Implementation(APlayerController* Controller);
		
	UFUNCTION()
		virtual FString GetInteractText() const;
};
