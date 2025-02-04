// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "EnemySoldierType.generated.h"

/**
 * 솔저 타입의 적 캐릭터 클래스
 */
UCLASS()
class PROJECTKTY_API AEnemySoldierType : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	void Attack_Shot();
};
