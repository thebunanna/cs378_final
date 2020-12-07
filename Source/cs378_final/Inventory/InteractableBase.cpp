// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"


void IInteractableBase::Interact_Implementation(APlayerController* Controller)
{
	return;
}

FString IInteractableBase::GetInteractText() const
{
	return FString::Printf(TEXT("string: Press F to action"));
}

