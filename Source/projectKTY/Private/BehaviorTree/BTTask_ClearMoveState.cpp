// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_ClearMoveState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "System/ShooterAIController.h"

UBTTask_ClearMoveState::UBTTask_ClearMoveState()
{
	NodeName = TEXT("Clear Move State");
}

EBTNodeResult::Type UBTTask_ClearMoveState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB)
	{
		return EBTNodeResult::Failed;
	}

	BB->SetValueAsEnum(FName("AIState"), static_cast<uint8>(EAIState::Idle));

	BB->SetValueAsBool(FName("bIsMoveCommanded"), false);

	return EBTNodeResult::Succeeded;
}
