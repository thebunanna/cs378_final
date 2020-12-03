// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../InventoryItem.h"
#include "../InventoryComponent.h"
#include "Templates/SubclassOf.h"
#include "InventoryWidget.h"
#include "InvSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class CS378_FINAL_API UInvSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FInventoryItem item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UInventoryWidget* inv;

	UFUNCTION(BlueprintCallable)
		FInventoryItem RemoveFromInv();
};
