// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/projectKTYCharacter.h"


UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI Pawn(or Character) Shoot Logic

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AprojectKTYCharacter* Character = Cast<AprojectKTYCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();

	return EBTNodeResult::Succeeded;
}
