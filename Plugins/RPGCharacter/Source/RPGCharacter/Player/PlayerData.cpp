// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

UPlayerData::UPlayerData()
{
	SavedArmor.Add(EArmorPartEnum::TORSO);
	SavedArmor.Add(EArmorPartEnum::LOWERLEFTARM);
	SavedArmor.Add(EArmorPartEnum::LOWERRIGHTARM);
	SavedArmor.Add(EArmorPartEnum::UPPERLEFTARM);
	SavedArmor.Add(EArmorPartEnum::UPPERRIGHTARM);
	SavedArmor.Add(EArmorPartEnum::LEFTHAND);
	SavedArmor.Add(EArmorPartEnum::RIGHTHAND);
	SavedArmor.Add(EArmorPartEnum::HIPS);
	SavedArmor.Add(EArmorPartEnum::LEFTLEG);
	SavedArmor.Add(EArmorPartEnum::RIGHTLEG);
}