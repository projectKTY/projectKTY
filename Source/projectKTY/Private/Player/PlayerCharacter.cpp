// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/PlayerCamera.h"
#include "Player/ShooterPlayerController.h"
#include "Character/WeaponManager.h"

APlayerCharacter::APlayerCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

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
		WeaponManager->GunFire();
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponManager != nullptr)
	{
		WeaponManager->SetGunMesh(this, TEXT("gun"));
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(GetController());
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully retrived PlayerController"));

		PlayerController->InputManager->Initialize(PlayerController, this);
		auto* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("Binding Input Actions..."));
			PlayerController->InputManager->BindInputActions(EnhancedInputComp);
		}
	}
}
