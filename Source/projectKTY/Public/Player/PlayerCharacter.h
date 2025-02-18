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

	virtual void Move(const FInputActionValue& Value) override;
	void UpdateMovementState(bool bMoving);

	void OnShot();
	void StopShooting();

	void OnZoom();
	void ReleaseZoom();

	UFUNCTION(BlueprintPure)
	UWeaponManager* GetWeaponManager();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UWeaponManager* WeaponManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UPlayerCamera* PlayerCamera;

	bool bIsMoving;
};
