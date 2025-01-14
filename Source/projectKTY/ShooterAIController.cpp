// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//// if LineOfSight
	//	// MoveTo
	//	// SetFocus
	//// else
	//	// ClearFocus
	//	// StopMovement
	//if (LineOfSightTo(PlayerCharacter))
	//{
	//	SetFocus(PlayerCharacter);
	//	MoveToActor(PlayerCharacter, AcceptanceRadius);
	//}
	//else
	//{
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerCharacter->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
