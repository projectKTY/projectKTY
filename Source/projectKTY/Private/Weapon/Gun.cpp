// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
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

