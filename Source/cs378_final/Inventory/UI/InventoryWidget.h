// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "InvSlotWidget.h"
#include "Templates/SubclassOf.h"
#include "Components/WrapBox.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class CS378_FINAL_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void LoadInventory();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class TSubclassOf<class UInvSlotWidget> BP_InvSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UWrapBox* InvPanel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UInventoryComponent* LinkedInv;
};
