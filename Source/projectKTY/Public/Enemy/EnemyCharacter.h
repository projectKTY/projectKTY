// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 적 캐릭터 클래스
 */

class UWeaponManager;

UCLASS()
class PROJECTKTY_API AEnemyCharacter : public ATPSCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UWeaponManager* WeaponManager;
};
