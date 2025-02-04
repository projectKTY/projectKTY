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
	// 나중에 플레이어와 다른 무기 체계를 가질 수도 있기 때문에 일단은 TPSCharacter 클래스에서 상속받지 않음
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UWeaponManager* WeaponManager;
};
