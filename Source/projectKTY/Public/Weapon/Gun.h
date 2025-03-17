// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/WeaponType.h"
#include "Gun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGunAmmoChangedDelegate, int32, CurrentAmmo, int32, Magazine);

UCLASS()
class PROJECTKTY_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	
	virtual void PullTrigger();
	virtual void Reload();
	virtual void ApplyRecoil();
	virtual void FireWeapon(FHitResult& Hit, FVector& ShotDirection);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleWeaponEffects(const FHitResult& Hit, const FVector& ShotDirection);

	void StartFiring();
	void StopFiring();
	
	void PlayReloadAnimation();

	FOnGunAmmoChangedDelegate OnGunAmmoChangedDelegate;

	void UpdateHUD();
	void DecreaseAmmoCount();
	void ResetAmmoCount();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmo() const { return CurrentAmmo; }
	
	UFUNCTION(BlueprintPure)
	int32 GetMagazine() const { return Magazine; }

	bool IsReloading() const { return bIsReloading; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Weapon")
	EWeaponType GetWeaponType() const { return WeaponType; }

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	UAnimMontage* ReloadMontage;
	
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	UFUNCTION()
	void FinishReload();

	AController* GetOwnerController() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	class UWeaponStatComponent* WeaponStatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType = EWeaponType::EWT_None;

	UPROPERTY(EditAnywhere)
	float MaxRange = 5000.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

	// Recoil Multiplication Value
	UPROPERTY(EditAnywhere)
	float RecoilAmount = 1.5f;

	// Recoil Random Pattern Range
	UPROPERTY(EditAnywhere)
	FVector2D RecoilPattern = FVector2D(0.5f, 1.0f);

	// AttackSpeed
	UPROPERTY(EditAnywhere)
	float FireRate = 1.0f;

	// Count of Magazine
	UPROPERTY(EditAnywhere)
	int32 Magazine = 9999;

	// Current Remain Ammo
	UPROPERTY(VisibleAnywhere)
	int32 CurrentAmmo;

	// Reload Time(Speed)
	UPROPERTY(EditAnywhere)
	float ReloadTime = 1.5f;

	FTimerHandle ReloadTimerHandle;
	bool bIsReloading = false;

	FTimerHandle FireTimerHandle;
	bool bIsFiring = false;
};
