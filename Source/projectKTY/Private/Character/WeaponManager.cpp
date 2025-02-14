// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WeaponManager.h"
#include "Character/TPSCharacter.h"
#include "Weapon/Gun.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponManager::SetGunMesh(ACharacter* Character, FName BoneName)
{
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	EquipWeapon(Gun);
	auto* Mesh = Character->GetMesh();
	Mesh->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	/*APlayerController* PlayerController = Cast<APlayerController>(Character->GetOwner());
	if (PlayerController) 
	{
		Gun->SetOwner(PlayerController);
	}*/
	Gun->SetOwner(Character);
	Gun->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	
}

void UWeaponManager::GunFire()
{
	/*if (Gun)
	{
		Gun->CreateMuzzleEffect();
		Gun->PullTrigger();
	}*/
	ServerSetFire();
	Gun->ApplyRecoil();
}

void UWeaponManager::StopGunFire()
{
	if (Gun)
	{
		Gun->StopFiring();
	}
}

bool UWeaponManager::HasGun()
{
	return Gun != nullptr;
}

EWeaponType UWeaponManager::GetCurrentWeaponType() const
{
	return EquippedWeapon ? EquippedWeapon->GetWeaponType() : EWeaponType::EWT_None;
}

void UWeaponManager::EquipWeapon(AGun* NewWeapon)
{
	if (NewWeapon)
	{
		EquippedWeapon = NewWeapon;
	}
}

bool UWeaponManager::IsRifle() const
{
	return false;
}

bool UWeaponManager::IsHandGun() const
{
	return false;
}

void UWeaponManager::MulticastSetFire_Implementation(const FHitResult& Hit, const FVector& ShotDirection)
{
	Gun->MulticastHandleWeaponEffects(Hit, ShotDirection);
}

void UWeaponManager::ServerSetFire_Implementation()
{
	if (Gun)
	{
		FHitResult Hit;
		FVector ShotDirection;

		Gun->FireWeapon(Hit, ShotDirection);
		MulticastSetFire(Hit, ShotDirection);
	}
}
