// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/PlayerCamera.h"
#include "Player/ShooterPlayerController.h"
#include "Character/WeaponManager.h"

APlayerCharacter::APlayerCharacter()
{
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	PlayerCamera = CreateDefaultSubobject<UPlayerCamera>(TEXT("PlayerCamera"));
	if (PlayerCamera != nullptr)
	{
		PlayerCamera->SetAttachmentToPlayer(this);
	}

	WeaponManager = CreateDefaultSubobject<UWeaponManager>(TEXT("WeaponManager"));
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

UWeaponManager* APlayerCharacter::GetWeaponManager()
{
	return WeaponManager;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponManager != nullptr)
	{
		WeaponManager->SetGunMesh(this, TEXT("weapon_r"));
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
