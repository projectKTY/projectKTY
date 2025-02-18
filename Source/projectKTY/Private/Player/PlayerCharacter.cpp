// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/PlayerCamera.h"
#include "Player/ShooterPlayerController.h"
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

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*bool bCurrentlyMoving = GetVelocity().SizeSquared() > 10.0f;
	if (bCurrentlyMoving != bIsMoving)
	{
		UpdateMovementState(bCurrentlyMoving);
	}*/
}
