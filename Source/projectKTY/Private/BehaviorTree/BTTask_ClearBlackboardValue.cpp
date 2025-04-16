// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

	BB->ClearValue(GetSelectedBlackboardKey());
	BB->SetValueAsVector(FName("LastKnownPlayerLocation"), FVector::ZeroVector);

	return EBTNodeResult::Succeeded;
}
