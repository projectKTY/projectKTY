// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "projectKTYGameMode.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTKTY_API AKillEmAllGameMode : public AprojectKTYGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* KilledPawn) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
