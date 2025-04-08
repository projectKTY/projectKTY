// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearMoveState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTKTY_API UBTTask_ClearMoveState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ClearMoveState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
