// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::CreateMuzzleEffect()
{
	// 발사 파티클 생성
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
}

void AGun::PlayMuzzleSound()
{
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
}

void AGun::StartFiring()
{
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

void AGun::PullTrigger()
{
	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		// 반동 적용
		ApplyRecoil();
		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		// UE_LOG(LogTemp, Warning, TEXT("%s Hit"), *Hit.GetActor()->GetName());
		PlayMuzzleSound();

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

void AGun::ApplyRecoil()
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController)
	{
		APawn* OwnerPawn = OwnerController->GetPawn();
		if (OwnerPawn)
		{
			APlayerController* PlayerController = Cast<APlayerController>(OwnerController);
			if (PlayerController)
			{
				FRotator CurrentRotation = PlayerController->GetControlRotation();

				float RecoilPitch = FMath::RandRange(RecoilPattern.X, RecoilPattern.Y) * RecoilAmount;
				float RecoilYaw = FMath::RandRange(-RecoilPattern.X, RecoilPattern.X) * RecoilAmount;

				FRotator NewRotation = FRotator(CurrentRotation.Pitch + RecoilPitch, CurrentRotation.Yaw + RecoilYaw, CurrentRotation.Roll);
				PlayerController->SetControlRotation(NewRotation);
			}
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
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
		return false;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
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

