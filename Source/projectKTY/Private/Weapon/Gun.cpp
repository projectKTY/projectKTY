// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Player/ShooterPlayerController.h"
#include "Player/PlayerCharacter.h"
#include "Weapon/WeaponStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	WeaponStatComponent = CreateDefaultSubobject<UWeaponStatComponent>(TEXT("WeaponStatComponent"));
}


void AGun::StartFiring()
{
	if (bIsReloading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun is Reloading, Cannot Fire"));
		return;
	}

	if (!bIsFiring)
	{
		bIsFiring = true;
		PullTrigger();

		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AGun::PullTrigger, FireRate, true);
	}
}

void AGun::StopFiring()
{
	bIsFiring = false;

	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void AGun::PlayReloadAnimation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter && ReloadMontage)
	{
		UAnimInstance* AnimInstance = PlayerCharacter->GetMesh()->GetAnimInstance();

		float MontageLength = ReloadMontage->GetPlayLength();
		float PlayRate = MontageLength / ReloadTime;

		if (AnimInstance)
		{
			AnimInstance->Montage_Play(ReloadMontage, PlayRate);
		}
	}
}

void AGun::UpdateHUD()
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(GetOwnerController());
	if (PlayerController)
	{
		PlayerController->UpdateHUD(CurrentAmmo, Magazine);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PC is NULL"));
	}
}


void AGun::DecreaseAmmoCount()
{
	--CurrentAmmo;
	UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %d"), CurrentAmmo);

	if (OnGunAmmoChangedDelegate.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("OnGunAmmoChangedDelegate is Bound"));
		OnGunAmmoChangedDelegate.Broadcast(CurrentAmmo, Magazine);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnGunAmmoChangedDelegate is not Bound"));
	}
}

void AGun::ResetAmmoCount()
{
	CurrentAmmo = Magazine;
}

void AGun::PullTrigger()
{
	// When During Reload, Don't Shoot 
	if (bIsReloading)
	{
		return;
	}

	if (CurrentAmmo > 0)
	{
		DecreaseAmmoCount();

		FHitResult Hit;
		FVector ShotDirection;

		bool bSuccess = GunTrace(Hit, ShotDirection);
		if (bSuccess)
		{
			// 반동 적용
			ApplyRecoil();
			// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
			// UE_LOG(LogTemp, Warning, TEXT("%s Hit"), *Hit.GetActor()->GetName());
			//PlayMuzzleSound();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

			AActor* HitActor = Hit.GetActor();
			if (HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				AController* OwnerController = GetOwnerController();
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
	else
	{
		Reload();
	}
}

void AGun::Reload()
{
	if (bIsReloading || CurrentAmmo == Magazine) return;

	bIsReloading = true;

	PlayReloadAnimation();

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("FinishReload"));

	GetWorldTimerManager().SetTimer(ReloadTimerHandle, TimerDelegate, ReloadTime, false);

	ResetAmmoCount();
}

void AGun::ApplyRecoil()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetOwnerController());
	if (PlayerController)                                                           
	{
		APawn* OwnerPawn = PlayerController->GetPawn();
		if (OwnerPawn)
		{
			FRotator CurrentRotation = PlayerController->GetControlRotation();

			float RecoilPitch = FMath::RandRange(RecoilPattern.X, RecoilPattern.Y) * RecoilAmount;
			float RecoilYaw = FMath::RandRange(-RecoilPattern.X, RecoilPattern.X) * RecoilAmount;

			FRotator NewRotation = FRotator(CurrentRotation.Pitch + RecoilPitch, CurrentRotation.Yaw + RecoilYaw, CurrentRotation.Roll);
			PlayerController->SetControlRotation(NewRotation);
		}
	}
}

void AGun::FireWeapon(FHitResult& Hit, FVector& ShotDirection)
{	
	bool Success = GunTrace(Hit, ShotDirection);
	if (Success)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	if (!OnGunAmmoChangedDelegate.IsBound())
	{
		UE_LOG(LogTemp, Error, TEXT("OnGunAmmoChangedDelegate is not bound in BeginPlay"));
	}

	Magazine = WeaponStatComponent->GetMagazine();
	CurrentAmmo = Magazine;
	ReloadTime = WeaponStatComponent->GetReloadtime();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Player Controller Not Found"));
		return false;
	}
		
	FVector Location;
	FRotator Rotation;

	APawn* OwnerPawn = OwnerController->GetPawn();	
	OwnerPawn->GetController()->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Owner);

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AGun::FinishReload()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
	CurrentAmmo = Magazine;
	bIsReloading = false;

	// 재장전 후에 HUD 업데이트를 위한 WeaponManager에게 알림처리
	if (OnGunAmmoChangedDelegate.IsBound())
	{
		OnGunAmmoChangedDelegate.Broadcast(CurrentAmmo, Magazine);
	}
}

void AGun::MulticastHandleWeaponEffects_Implementation(const FHitResult& Hit, const FVector& ShotDirection)
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	}

	if (MuzzleSound)
	{

		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	}

	if (ImpactEffect)
	{

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
	}

	if (ImpactSound)
	{

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
	}
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();
}
