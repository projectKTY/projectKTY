// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 플레이어 캐릭터 클래스
 */

class UWeaponManager;
class UPlayerCamera;

UCLASS()
class PROJECTKTY_API APlayerCharacter : public ATPSCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	void OnShot();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UWeaponManager* WeaponManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UPlayerCamera* PlayerCamera;
};
