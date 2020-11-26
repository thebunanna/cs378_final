#pragma once

#include "CharacterStates.generated.h"

UENUM(BlueprintType)
enum class ECharacterStateEnum : uint8
{
	IDLE UMETA(DisplayName = "Idling"),
	MOVE UMETA(DisplayName = "Moving"),
	RUN UMETA(DisplayName = "Running"),
	ATTACK UMETA(DisplayName = "Attacking"),
	BLOCK UMETA(DisplayName = "Blocking"),
	DEAD UMETA(DisplayName = "Dead")
};