// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/projectKTYCharacter.h"
#include "Character/TPSCharacter.h"

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const
{
	ATPSCharacter* ControlledCharacter = Cast<ATPSCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	/*if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		if (GetBlackboardComponent() && GetPawn())
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Blackboard or Pawn is NULL in AIController::BeginPlay"));
		}
	}*/
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		if (GetBlackboardComponent() && InPawn)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), InPawn->GetActorLocation());
		}
	}
}
