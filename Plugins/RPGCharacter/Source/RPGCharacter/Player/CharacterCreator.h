// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerData.h"

#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterCreator.generated.h"

UCLASS()
class RPGCHARACTER_API ACharacterCreator : public ACharacter
{
	GENERATED_BODY()

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPlayerData* data;
	
public:	
	// Sets default values for this actor's properties
	ACharacterCreator();

	UMaterialInstanceDynamic* material;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		bool Gender;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> HeadOptions_Female;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> HeadOptions_Male;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		int HeadIndex;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Head;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> HairOptions;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		int HairIndex;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Hair;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> EyebrowsOptions_Female;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> EyebrowsOptions_Male;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		int EyebrowsIndex;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Eyebrows;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		TArray<USkeletalMesh*> FacialHairOptions;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		int FacialHairIndex;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* FacialHair;

	// ----------
	// Swap Parts
	// ----------

	UFUNCTION(BlueprintCallable)
		void ChangeName(FString NewName);

	UFUNCTION(BlueprintCallable)
		void ChangeGender(bool NewGender);

	UFUNCTION(BlueprintCallable)
		void ChangeHead(int value);

	UFUNCTION(BlueprintCallable)
		void ChangeHair(int value);

	UFUNCTION(BlueprintCallable)
		void ChangeEyebrows(int value);

	UFUNCTION(BlueprintCallable)
		void ChangeFacialHair(int value);

	UFUNCTION(BlueprintCallable)
		void RotateFace(float value);

	// -------------
	// Change Colors
	// -------------

	UFUNCTION(BlueprintCallable)
		void SkinColor(float r, float g, float b);

	UFUNCTION(BlueprintCallable)
		void PaintColor(float r, float g, float b);

	UFUNCTION(BlueprintCallable)
		void HairColor(float r, float g, float b);

	UFUNCTION(BlueprintCallable)
		void Save();
};
