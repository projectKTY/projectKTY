// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WeaponManager.h"
#include "Character/TPSCharacter.h"
#include "Player/ShooterPlayerController.h"
#include "Player/PlayerCharacter.h"
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
}

void UWeaponManager::SetGunMesh(ACharacter* Character, FName BoneName)
{
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	EquipWeapon(Character, Gun);
	auto* Mesh = Character->GetMesh();
	Mesh->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
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
}

void UWeaponManager::StopGunFire()
{
	if (Gun)
	{
		Gun->StopFiring();
	}
}

void UWeaponManager::ReloadWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Reload();
	}
}

bool UWeaponManager::HasGun()
{
	return Gun != nullptr;
}

EWeaponType UWeaponManager::GetCurrentWeaponType() const
{
	return EquippedWeapon ? EquippedWeapon->GetWeaponType() : EWeaponType::EWT_AssaultRifle;
}

void UWeaponManager::EquipWeapon(ACharacter* Character, AGun* NewWeapon)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
	if (PlayerCharacter)
	{
		// OnAmmoChangedDelegate.RemoveDynamic(PlayerCharacter, &APlayerCharacter::OnAmmoChanged);
		OnAmmoChangedDelegate.AddDynamic(PlayerCharacter, &APlayerCharacter::OnAmmoChanged);
	}
	if (EquippedWeapon)
	{
		EquippedWeapon->OnGunAmmoChangedDelegate.RemoveDynamic(this, &UWeaponManager::NotifyAmmoChanged);
		EquippedWeapon->OnGunAmmoChangedDelegate.RemoveAll(this);
	}


	if (NewWeapon)
	{
		EquippedWeapon = NewWeapon;
		EquippedWeapon->SetOwner(Character);
		EquippedWeapon->OnGunAmmoChangedDelegate.AddDynamic(this, &UWeaponManager::NotifyAmmoChanged);
		if (EquippedWeapon->OnGunAmmoChangedDelegate.IsBound())
		{
			UE_LOG(LogTemp, Warning, TEXT("WeaponManager Successfully bound to OnGunAmmoChangedDelegate"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("WeaponManager failed to bound OnGunAmmoChangedDelegate"));
		}
		NotifyAmmoChanged(EquippedWeapon->GetCurrentAmmo(), EquippedWeapon->GetMagazine());
		EquippedWeapon->UpdateHUD();
	}
}

void UWeaponManager::NotifyAmmoChanged(int32 CurrentAmmo, int32 Magazine)
{
	if (OnAmmoChangedDelegate.IsBound())
	{
		OnAmmoChangedDelegate.Broadcast(CurrentAmmo, Magazine);
		UE_LOG(LogTemp, Warning, TEXT("NotifyAmmoChanged is working"));

		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
		if (PlayerCharacter)
		{
			AShooterPlayerController* PC = Cast<AShooterPlayerController>(PlayerCharacter->GetController());
			if (PC && PC->IsLocalController())
			{
				PC->UpdateHUD(CurrentAmmo, Magazine);
			}
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NotifyAmmoChanged is not working"));
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

void UWeaponManager::ChangeWeapon(ACharacter* Character, EWeaponType NewWeaponType)
{
	UE_LOG(LogTemp, Warning, TEXT("Call Change Weapon Function..."));
	// 이미 착용한 무기와 동일 변경액션 x
	if (EquippedWeapon && EquippedWeapon->GetWeaponType() == NewWeaponType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Same Weapon Equipped"));
		return;
	}

	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}

	GunClass = WeaponClasses[NewWeaponType];
	SetGunMesh(Character, TEXT("weapon_r"));

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

		// Gun->FireWeapon(Hit, ShotDirection);
		if (Gun->IsReloading())
		{
			UE_LOG(LogTemp, Warning, TEXT("Gun is Reloading"));
		}
		else
		{
			Gun->StartFiring();
			MulticastSetFire(Hit, ShotDirection);
		}
	}
}
