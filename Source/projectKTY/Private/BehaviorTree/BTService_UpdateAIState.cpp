// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_UpdateAIState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "System/ShooterAIController.h"
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
		BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Dead));
		return;
	}

	// 2. IsMoveCommanded 체크
	bool bMoveCommanded = BB->GetValueAsBool(TEXT("bIsMoveCommanded"));
	if (bMoveCommanded)
	{
		BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Move));
		// LastKnownPlayerLocation 초기화
		BB->ClearValue(FName("LastKnownPlayerLocation"));
		return;
	}

	if (BB->GetValueAsEnum(AIStateKey.SelectedKeyName) != static_cast<uint8>(EAIState::Move))
	{
		// 2. 타겟 추출
		AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));

		if (TargetActor)
		{
			float Distance = FVector::Dist(TargetActor->GetActorLocation(), ControlledPawn->GetActorLocation());

			if (Distance <= AttackRange)
			{
				BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Attack));
			}
			else
			{
				BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Chase));
			}
		}
		else
		{
			FVector LastKnownLocation = BB->GetValueAsVector(LastKnownLocationKey.SelectedKeyName);
			if (!LastKnownLocation.IsNearlyZero())
			{
				BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Retreat));
			}
			else
			{
				BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Idle));
			}
		}
	}
}
