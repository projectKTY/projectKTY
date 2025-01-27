// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTKTY_API APlayerCharacter : public ATPSCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
};
