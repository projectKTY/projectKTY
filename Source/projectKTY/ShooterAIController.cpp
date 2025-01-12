// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// if LineOfSight
		// MoveTo
		// SetFocus
	// else
		// ClearFocus
		// StopMovement
	if (LineOfSightTo(PlayerCharacter))
	{
		SetFocus(PlayerCharacter);
		MoveToActor(PlayerCharacter, AcceptanceRadius);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
}
