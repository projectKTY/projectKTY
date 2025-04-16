// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_SetAIState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_SetAIState::UBTTask_SetAIState()
{
	NodeName = TEXT("Set AI State");
}

EBTNodeResult::Type UBTTask_SetAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB)
	{
		return EBTNodeResult::Failed;
	}

	BB->SetValueAsEnum(AIStateKey.SelectedKeyName, static_cast<uint8>(NewState));
	return EBTNodeResult::Succeeded;
}
