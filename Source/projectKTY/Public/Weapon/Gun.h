// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_None			UMETA(DisplayName = "None"),
	EWT_AssaultRifle	UMETA(DisplayName = "Assault Rifle"),
	EWT_HandGun			UMETA(DisplayName = "HandGun"),
	EWT_SniperRifle		UMETA(DisplayName = "Sniper Rifle"),
	EWT_Shotgun			UMETA(DisplayName = "Shotgun")
};

UCLASS()
class PROJECTKTY_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	
	virtual void PullTrigger();
	virtual void ApplyRecoil();
	virtual void FireWeapon(FHitResult& Hit, FVector& ShotDirection);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleWeaponEffects(const FHitResult& Hit, const FVector& ShotDirection);
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
	
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType WeaponType = EWeaponType::EWT_None;

	// 총기 최대 사거리
	UPROPERTY(EditAnywhere)
	float MaxRange = 5000.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

	// 반동 크기
	UPROPERTY(EditAnywhere)
	float RecoilAmount = 1.5f;

	// 반동 랜덤값
	UPROPERTY(EditAnywhere)
	FVector2D RecoilPattern = FVector2D(0.5f, 1.0f);



};
