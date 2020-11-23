// Fill out your copyright notice in the Description page of Project Settings.


#include "CS378FinalGameState.h"

ACS378FinalGameState::ACS378FinalGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
	ItemDB = BP_ItemDB.Object;
}

UDataTable* ACS378FinalGameState::GetItemDB() const
{
	return ItemDB;
}