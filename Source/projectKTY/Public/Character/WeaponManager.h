// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"

/**
*  캐릭터에게 부착되어 무기류를 관리하는 액터 컴포넌트
*/

class AGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTKTY_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetGunMesh(ACharacter* Character, FName BoneName);
	void GunFire();
	void StopGunFire();
	bool HasGun();

	UFUNCTION(BlueprintCallable)
	EWeaponType GetCurrentWeaponType() const;

	void EquipWeapon(AGun* NewWeapon);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY()
	AGun* Gun;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGun* EquippedWeapon;

public:
	UFUNCTION(BlueprintPure)
	bool IsRifle() const;

	UFUNCTION(BlueprintPure)
	bool IsHandGun() const;

protected:
	UFUNCTION(Server, Reliable)
	void ServerSetFire();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetFire();
};
