// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/projectKTYGameMode.h"
#include "Character/projectKTYCharacter.h"
#include "UObject/ConstructorHelpers.h"

AprojectKTYGameMode::AprojectKTYGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Characters/Player/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AprojectKTYGameMode::PawnKilled(APawn* KilledPawn)
{
}
