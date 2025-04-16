// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "System/ShooterAIController.h"
#include "BTTask_SetAIState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTKTY_API UBTTask_SetAIState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetAIState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector AIStateKey;

	UPROPERTY(EditAnywhere)
	EAIState NewState;
};
