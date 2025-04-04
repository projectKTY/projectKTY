// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/PlayerCamera.h"
#include "Player/ShooterPlayerController.h"
#include "Weapon/WeaponType.h"
#include "Character/WeaponManager.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UPlayerCamera>(TEXT("PlayerCamera"));
	if (PlayerCamera != nullptr)
	{
		PlayerCamera->SetAttachmentToPlayer(this);
	}

	WeaponManager = CreateDefaultSubobject<UWeaponManager>(TEXT("WeaponManager"));

	bIsMoving = false;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	Super::Move(Value);

	/*FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr && MovementVector != FVector2D::ZeroVector)
	{
		if (!bIsMoving)
		{
			UpdateMovementState(true);
		}
	}*/
}

void APlayerCharacter::UpdateMovementState(bool bMoving)
{
	if (bIsMoving == bMoving) return;
	bIsMoving = bMoving;

	if (PlayerCamera)
	{
		PlayerCamera->SetCameraMode(bIsMoving);
	}
}

void APlayerCharacter::OnShot()
{
	if (WeaponManager != nullptr)
	{
		// 조준 중일 때만 사격 가능하도록
		if (bIsAiming)
		{
			WeaponManager->GunFire();
		}
	}
}

void APlayerCharacter::StopShooting()
{
	if (WeaponManager != nullptr)
	{
		WeaponManager->StopGunFire();
	}
}

void APlayerCharacter::OnZoom()
{
	if (PlayerCamera != nullptr)
	{
		PlayerCamera->ZoomIn();		
	}
}

void APlayerCharacter::ReleaseZoom()
{
	if (PlayerCamera != nullptr)
	{
		PlayerCamera->ZoomOut();
	}
}

void APlayerCharacter::StartReload()
{
	if (WeaponManager && WeaponManager->HasGun())
	{
		WeaponManager->ReloadWeapon();
	}
}

void APlayerCharacter::SelectWeapon1()
{
	if (WeaponManager)
	{
		WeaponManager->ChangeWeapon(this, EWeaponType::EWT_AssaultRifle);
	}
}

void APlayerCharacter::SelectWeapon2()
{
	if (WeaponManager)
	{
		WeaponManager->ChangeWeapon(this, EWeaponType::EWT_HandGun);
	}
}

void APlayerCharacter::SelectWeapon3()
{
	if (WeaponManager)
	{
		WeaponManager->ChangeWeapon(this, EWeaponType::EWT_SniperRifle);
	}
}

void APlayerCharacter::UIToggle()
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->ToggleCursorMode();
	}
}

UWeaponManager* APlayerCharacter::GetWeaponManager()
{
	return WeaponManager;
}

void APlayerCharacter::OnAmmoChanged(int32 CurrentAmmo, int32 Magazine)
{
	UE_LOG(LogTemp, Warning, TEXT("OnAmmoChanged Call"));
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->UpdateHUD(CurrentAmmo, Magazine);
		UE_LOG(LogTemp, Warning, TEXT("OnAmmoChanged is working"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnAmmoChanged in PlayerCharacter.cpp not working"));
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponManager != nullptr)
	{
		WeaponManager->SetGunMesh(this, TEXT("weapon_r"));
		// WeaponManager->InitializeWeapons(this);
		// WeaponManager->EquipWeaponByType(EWeaponType::EWT_AssaultRifle);
		// WeaponManager->OnAmmoChangedDelegate.AddDynamic(this, &APlayerCharacter::OnAmmoChanged);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(GetController());
	if (PlayerController)
	{

		PlayerController->InputManager->Initialize(PlayerController, this);
		auto* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("Binding Input Actions..."));
			PlayerController->InputManager->BindInputActions(EnhancedInputComp);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*bool bCurrentlyMoving = GetVelocity().SizeSquared() > 10.0f;
	if (bCurrentlyMoving != bIsMoving)
	{
		UpdateMovementState(bCurrentlyMoving);
	}*/
}
