#pragma once

#include "ArmorTypes.generated.h"

UENUM(BlueprintType)
enum class EArmorPartEnum : uint8
{
	TORSO UMETA(DisplayName = "Torso"),
	LOWERLEFTARM UMETA(DisplayName = "Lower Left Arm"),
	LOWERRIGHTARM UMETA(DisplayName = "Lower Right Arm"),
	UPPERLEFTARM UMETA(DisplayName = "Upper Left Arm"),
	UPPERRIGHTARM UMETA(DisplayName = "Upper Right Arm"),
	LEFTHAND UMETA(DisplayName = "Left Hand"),
	RIGHTHAND UMETA(DisplayName = "Right Hand"),
	HIPS UMETA(DisplayName = "Hips"),
	LEFTLEG UMETA(DisplayName = "Left Leg"),
	RIGHTLEG UMETA(DisplayName = "Right Leg")
};

UENUM(BlueprintType)
enum class EArmorTypeEnum : uint8
{
	NONE UMETA(DisplayName = "None")
};