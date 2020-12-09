// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularPlayerCharacter.h"
#include "CharacterCreator.h"

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
    void Pause();

	UFUNCTION(BlueprintCallable)
		void EquipArmor(TSubclassOf<AArmor> armor);

	UFUNCTION(BlueprintCallable)
		void ChangeGender(bool gender);

	UFUNCTION(BlueprintCallable)
		void ChangeHair(float value);

	UFUNCTION(BlueprintCallable)
		void ChangeHead(float value);

	UFUNCTION(BlueprintCallable)
		void ChangeEyebrows(float value);

	UFUNCTION(BlueprintCallable)
		void ChangeFacialHair(float value);

	UFUNCTION(BlueprintCallable)
		void SkinColor(float r, float g, float b);

	UFUNCTION(BlueprintCallable)
		void PaintColor(float r, float g, float b);

	UFUNCTION(BlueprintCallable)
		void HairColor(float r, float g, float b);

	UFUNCTION(BlueprintCallable)
		void Save();
};
