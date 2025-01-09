// Copyright Epic Games, Inc. All Rights Reserved.

#include "projectKTYGameMode.h"
#include "projectKTYCharacter.h"
#include "UObject/ConstructorHelpers.h"

AprojectKTYGameMode::AprojectKTYGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
