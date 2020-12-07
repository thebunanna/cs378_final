// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "Math/UnrealMathUtility.h"
FInventoryItem::FInventoryItem()
{
	static int32 next = 0;
	this->Name = FText::FromString("No Name");
	this->Value = 1;
	this->Description = FText::FromString("No Description");
}
