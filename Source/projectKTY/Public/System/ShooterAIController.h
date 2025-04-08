// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Move UMETA(DisplayName = "Move"),
	Chase UMETA(DisplayName = "Chase"),
	Attack UMETA(DisplayName = "Attack"),
	Retreat UMETA(DisplayName = "Retreat"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class PROJECTKTY_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	// UPROPERTY(EditAnywhere)
	// float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
