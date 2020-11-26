// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularPlayerCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ModularPlayerController.generated.h"

/**
 *
 */
UCLASS()
class RPGCHARACTER_API AModularPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AModularPlayerController();

protected:
	virtual void SetupInputComponent() override;

public:
	void Forward(float value);
	void Right(float value);
	void CameraY(float value);
	void CameraX(float value);

	void Attack();
	void Block();
	void StopBlock();
};
