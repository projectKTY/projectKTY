// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_UpdateAIState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"


UBTService_UpdateAIState::UBTService_UpdateAIState()
{
	NodeName = TEXT("Update AI State");
	Interval = 0.35f;
	RandomDeviation = 0.05f;
}

void UBTService_UpdateAIState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

	if (!BB || !ControlledPawn) return;

	// 1. IsDead 체크
	bool bIsDead = BB->GetValueAsBool(IsDeadKey.SelectedKeyName);
	if (bIsDead || ControlledPawn->IsPendingKill())
	{
		BB->SetValueAsName(AIStateKey.SelectedKeyName, FName("Dead"));
		return;
	}

	// 2. 타겟 추출
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (TargetActor)
	{
		float Distance = FVector::Dist(TargetActor->GetActorLocation(), ControlledPawn->GetActorLocation());

		if (Distance <= AttackRange)
		{
			BB->SetValueAsName(AIStateKey.SelectedKeyName, FName("Attack"));
		}
		else
		{
			BB->SetValueAsName(AIStateKey.SelectedKeyName, FName("Chase"));
		}
	}
	else
	{
		FVector LastKnownLocation = BB->GetValueAsVector(LastKnownLocationKey.SelectedKeyName);
		if (!LastKnownLocation.IsNearlyZero())
		{
			BB->SetValueAsName(AIStateKey.SelectedKeyName, FName("Retreat"));
		}
		else
		{
			BB->SetValueAsName(AIStateKey.SelectedKeyName, FName("Idle"));
		}
	}
}
