// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "projectKTYGameMode.generated.h"

UCLASS(minimalapi)
class AprojectKTYGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AprojectKTYGameMode();

	virtual void PawnKilled(APawn* KilledPawn);
};



