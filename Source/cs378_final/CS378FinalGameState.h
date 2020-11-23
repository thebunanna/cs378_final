// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/GameState.h"
#include "CS378FinalGameState.generated.h"

/**
 * 
 */
UCLASS()
class CS378_FINAL_API ACS378FinalGameState : public AGameState
{
	GENERATED_BODY()

public:
	ACS378FinalGameState();
	UDataTable* GetItemDB() const;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemDB;
};
