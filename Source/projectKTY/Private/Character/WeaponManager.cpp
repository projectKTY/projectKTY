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
	Gun->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(Character);
}

void UWeaponManager::GunFire()
{
	/*if (Gun)
	{
		Gun->CreateMuzzleEffect();
		Gun->PullTrigger();
	}*/
	ServerSetFire();
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

void UWeaponManager::MulticastSetFire_Implementation()
{
	if (Gun)
	{
		Gun->CreateMuzzleEffect();
	}
}

void UWeaponManager::ServerSetFire_Implementation()
{
	if (Gun)
	{
		Gun->StartFiring();
		MulticastSetFire();
	}
}
