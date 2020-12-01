#pragma once

#include "WeaponTypes.generated.h"

UENUM(BlueprintType)
enum class EWeaponTypeEnum : uint8
{
	NONE UMETA(DisplayName = "None"),
	SWORD UMETA(DisplayName = "Sword"),
	SHIELD UMETA(DisplayName = "Shield")
};