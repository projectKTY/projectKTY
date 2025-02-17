// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSCharacter.h"
#include "Engine/LocalPlayer.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Character/CharacterStatComponent.h"
#include "GameMode/projectKTYGameMode.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Character Stat Component
	StatComponent = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("StatComponent"));
}

float ATPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		// Server
		MulticastSetDie();

		// client
		AprojectKTYGameMode* GameMode = GetWorld()->GetAuthGameMode<AprojectKTYGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool ATPSCharacter::IsDead() const
{
	return Health <= 0;
}

float ATPSCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void ATPSCharacter::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void ATPSCharacter::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(DeadMontage);
	}
}

void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacterMovement())
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterMovementComponent is valid."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterMovementComponent is NULL! Movement won't work."));
	}

	SetDefaultStatus();
}

void ATPSCharacter::SetDefaultStatus()
{
	MaxHealth = StatComponent->GetMaxHp();
	Health = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Character Health: %d"), Health);
	WalkSpeed = StatComponent->GetSpeed() * 100;
	SprintSpeed = WalkSpeed * 2;

	SetDefaultCharacterSettings();
}

void ATPSCharacter::SetDefaultCharacterSettings()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}



void ATPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// UE_LOG(LogTemp, Warning, TEXT("MoveForward called with X: %f, Y: %f"), MovementVector.X, MovementVector.Y);

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward and right vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 로그 추가 (이동 벡터 확인)
		// UE_LOG(LogTemp, Warning, TEXT("Applying movement: Forward: %f, Right: %f"), MovementVector.Y, MovementVector.X);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		// UE_LOG(LogTemp, Warning, TEXT("AddMovement() Called"));
	}
}

void ATPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATPSCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsSprinting = true;

	UE_LOG(LogTemp, Warning, TEXT("Sprint() Called"));

	if (HasAuthority() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully Server Sprint() Called"));
		ServerSetSprint(true);
	}
}

void ATPSCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsSprinting = false;

	UE_LOG(LogTemp, Warning, TEXT("StopSprint() Called"));
	if (HasAuthority() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully Server StopSprint() Called"));
		ServerSetSprint(false);
	}
}

void ATPSCharacter::StartAiming()
{
	ServerSetAim(true);
}

void ATPSCharacter::StopAiming()
{
	ServerSetAim(false);
}

void ATPSCharacter::ServerSetSprint_Implementation(bool IsSprinting)
{
	if (IsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void ATPSCharacter::MulticastSetDie_Implementation()
{
	SetDead();
}


void ATPSCharacter::ServerSetAim_Implementation(bool IsAim)
{
	MulticastSetAim(IsAim);
}

void ATPSCharacter::MulticastSetAim_Implementation(bool IsAim)
{
	bIsAiming = IsAim;
}
