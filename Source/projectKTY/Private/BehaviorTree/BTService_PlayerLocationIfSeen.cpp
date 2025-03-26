// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!BB || !AIController || !PlayerCharacter)
	{
		return;
	}

	if (AIController->LineOfSightTo(PlayerCharacter))
	{
		// 플레이어가 보이면 타겟 등록 + 마지막 위치 갱신
		BB->SetValueAsObject(GetSelectedBlackboardKey(), PlayerCharacter);
		BB->SetValueAsVector(FName("LastKnownPlayerLocation"), PlayerCharacter->GetActorLocation());
	}
	else
	{
		// 플레이어가 보이지 않으면 TargetActor를 비움
		// LastKnownPlayerLocation은 유지
		BB->ClearValue(GetSelectedBlackboardKey());
	}
}
