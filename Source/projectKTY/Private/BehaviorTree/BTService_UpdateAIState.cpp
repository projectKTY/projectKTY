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

	// 사망 상태 확인
	bool bIsDead = BB->GetValueAsBool(IsDeadKey.SelectedKeyName);
	if (bIsDead || ControlledPawn->IsPendingKill())
	{
		BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Dead));
		return;
	}

	// 수동 이동 상태(Move)는 서비스에서 덮어쓰지 않도록 예외 처리
	if (BB->GetValueAsEnum(AIStateKey.SelectedKeyName) == static_cast<uint8>(EAIState::Move))
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));
	UE_LOG(LogTemp, Warning, TEXT("TargetActor: %s"), TargetActor ? *TargetActor->GetName() : TEXT("NULL"));
	FVector LastKnownLocation = BB->GetValueAsVector(LastKnownLocationKey.SelectedKeyName);
	FVector SpawnLocation = BB->GetValueAsVector(SpawnLocationKey.SelectedKeyName);

	// 플레이어 인식 여부 판단 (라인트레이스 기반)
	bool bCanSeePlayer = false;
	if (TargetActor && AIController->LineOfSightTo(TargetActor))
	{
		bCanSeePlayer = true;
		BB->SetValueAsVector(LastKnownLocationKey.SelectedKeyName, TargetActor->GetActorLocation());
		BB->SetValueAsObject(TargetActorKey.SelectedKeyName, TargetActor);
	}
	else
	{
		BB->ClearValue(TargetActorKey.SelectedKeyName);
	}

	// 상태 업데이트 로직
	if (bCanSeePlayer)
	{
		float DistanceToPlayer = FVector::Dist(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Distance to Target: %f"), DistanceToPlayer);
		float AttackRangeValue = 500.0f;

		if (DistanceToPlayer <= AttackRangeValue)
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
		// 플레이어를 인식하지 못하고 LastKnownLocation이 있다면 후퇴 상태
		if (!LastKnownLocation.IsNearlyZero())
		{
			BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Retreat));
		}
		else
		{
			// 완전히 인식하지 못한 상태라면 Idle
			BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(EAIState::Idle));
		}
	}
}
