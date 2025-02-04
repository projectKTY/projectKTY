// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/projectKTYCharacter.h"
#include "Character/TPSCharacter.h"
#include "Enemy/EnemySoldierType.h"


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

	ATPSCharacter* Character = Cast<ATPSCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	// Change to Enemy Character class and check has gun
	AEnemySoldierType* EnemyCharacter = Cast<AEnemySoldierType>(Character);
	EnemyCharacter->Attack_Shot();

	return EBTNodeResult::Succeeded;
}
