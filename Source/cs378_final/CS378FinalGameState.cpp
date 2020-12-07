// Fill out your copyright notice in the Description page of Project Settings.


#include "CS378FinalGameState.h"

ACS378FinalGameState::ACS378FinalGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
	ItemDB = BP_ItemDB.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ArmourDB(TEXT("DataTable'/Game/Data/ArmourDB.ArmourDB'"));
	ArmorDB = BP_ArmourDB.Object;
}

UDataTable* ACS378FinalGameState::GetItemDB() const
{
	return ItemDB;
}

UDataTable* ACS378FinalGameState::GetArmorDB() const
{
	return ArmorDB;
}