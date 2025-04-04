// Fill out your copyright notice in the Description page of Project Settings.


#include "System/TPSInputManager.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "ShooterPlayerController.generated.h"
#include "Player/PlayerCharacter.h"

UTPSInputManager::UTPSInputManager()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_MOVE(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ThirdPerson/Input/IMC_Default.IMC_Default'"));
	if (IMC_MOVE.Succeeded())
	{
		DefaultMappingContext = IMC_MOVE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move'"));
	if (IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Look.IA_Look'"));
	if (IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Jump.IA_Jump'"));
	if (IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SPRINT(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Sprint.IA_Sprint'"));
	if (IA_SPRINT.Succeeded())
	{
		SprintAction = IA_SPRINT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SHOT(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Shoot.IA_Shoot'"));
	if (IA_SHOT.Succeeded())
	{
		ShootAction = IA_SHOT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_AIMING(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Aiming.IA_Aiming'"));
	if (IA_AIMING.Succeeded())
	{
		AimingAction = IA_AIMING.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_RELOAD(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Reload.IA_Reload'"));
	if (IA_RELOAD.Succeeded())
	{
		ReloadAction = IA_RELOAD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SELECTWEAPON_1(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Weapon1.IA_Weapon1'"));
	if (IA_SELECTWEAPON_1.Succeeded())
	{
		SelectWeapon1Action = IA_SELECTWEAPON_1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SELECTWEAPON_2(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Weapon2.IA_Weapon2'"));
	if (IA_SELECTWEAPON_2.Succeeded())
	{
		SelectWeapon2Action = IA_SELECTWEAPON_2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SELECTWEAPON_3(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Weapon3.IA_Weapon3'"));
	if (IA_SELECTWEAPON_3.Succeeded())
	{
		SelectWeapon3Action = IA_SELECTWEAPON_3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_UI_TOGGLE(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_UIToggle.IA_UIToggle'"));
	if (IA_UI_TOGGLE.Succeeded())
	{
		UIToggleAction = IA_UI_TOGGLE.Object;
	}
}

void UTPSInputManager::Initialize(APlayerController* PlayerController, ATPSCharacter* ControlledCharacter)
{
	Character = ControlledCharacter;
	
	UE_LOG(LogTemp, Error, TEXT("InputManager Initialize 1"));

	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("InputManager Initialize failed : Character is nullptr"));
	}

	if (PlayerController)
	{
		auto* LocalPlayer = PlayerController->GetLocalPlayer();
		UE_LOG(LogTemp, Error, TEXT("InputManager's LocalPlayer Name: %s"), *LocalPlayer->GetName());
		EnhancedInputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		if (!DefaultMappingContext)
		{
			UE_LOG(LogTemp, Error, TEXT("DefaultMappingContext is NULL!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext Loaded Successfully!"));
		}

		if (EnhancedInputSubSystem)
		{
			UE_LOG(LogTemp, Warning, TEXT("EnhancedInputSubsystem Loaded Successfully!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("EnhancedInputSubsystem is NULL! Check LocalPlayer reference!"));
		}


		if (EnhancedInputSubSystem && DefaultMappingContext)
		{
			UE_LOG(LogTemp, Error, TEXT("InputManager Add Mapping Context"));
			EnhancedInputSubSystem->ClearAllMappings();
			EnhancedInputSubSystem->AddMappingContext(DefaultMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Mapping Context Added Successfully!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot Add Mapping Context! Subsystem or DefaultMappingContext is NULL!"));
		}
	}
}

void UTPSInputManager::BindInputActions(UEnhancedInputComponent* InputComponent)
{
	if (!InputComponent || !Character)
	{
		UE_LOG(LogTemp, Error, TEXT("InputManager Bind Actions Failled!"));
		if (!Character)
		{
			UE_LOG(LogTemp, Error, TEXT("InputManager does have not a Character!"));
		}
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("InputManager Bind Actions!"));

	// Moving
	InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UTPSInputManager::OnMove);

	// Looking
	InputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UTPSInputManager::OnLook);

	// Jumping
	InputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UTPSInputManager::OnJump);
	InputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UTPSInputManager::OnStopJumping);

	// Sprinting
	InputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &UTPSInputManager::OnSprint);
	InputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &UTPSInputManager::OnStopSprint);

	// Shooting
	InputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &UTPSInputManager::OnShoot);
	InputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &UTPSInputManager::OnStopShoot);

	// Aiming
	InputComponent->BindAction(AimingAction, ETriggerEvent::Started, this, &UTPSInputManager::OnAiming);
	InputComponent->BindAction(AimingAction, ETriggerEvent::Completed, this, &UTPSInputManager::OnStopAiming);

	// Reload
	InputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UTPSInputManager::OnReload);

	// Select Weapons
	InputComponent->BindAction(SelectWeapon1Action, ETriggerEvent::Started, this, &UTPSInputManager::SelectWeapon1);
	InputComponent->BindAction(SelectWeapon2Action, ETriggerEvent::Started, this, &UTPSInputManager::SelectWeapon2);
	InputComponent->BindAction(SelectWeapon3Action, ETriggerEvent::Started, this, &UTPSInputManager::SelectWeapon3);

	// UI Toggle
	InputComponent->BindAction(UIToggleAction, ETriggerEvent::Started, this, &UTPSInputManager::UIToggle);
}

void UTPSInputManager::OnMove(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->Move(Value);
	}
}

void UTPSInputManager::OnLook(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->Look(Value);
	}
}

void UTPSInputManager::OnJump()
{
	if (Character)
	{
		Character->Jump();
	}
}

void UTPSInputManager::OnStopJumping()
{
	if (Character)
	{
		Character->StopJumping();
	}
}

void UTPSInputManager::OnSprint()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		if (PlayerCharacter->IsAiming())
		{
			PlayerCharacter->ReleaseZoom();
			PlayerCharacter->StopAiming();
		}
		Character->Sprint();
	}
}

void UTPSInputManager::OnStopSprint()
{
	if (Character)
	{
		Character->StopSprint();
	}
}

void UTPSInputManager::OnShoot()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->OnShot();
	}
}

void UTPSInputManager::OnStopShoot()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->StopShooting();
	}
}

void UTPSInputManager::OnAiming()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		if (PlayerCharacter->bIsSprinting)
		{
			PlayerCharacter->StopSprint();
		}
		PlayerCharacter->OnZoom();
		PlayerCharacter->StartAiming();
	}
}

void UTPSInputManager::OnStopAiming()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->ReleaseZoom();
		PlayerCharacter->StopAiming();
	}
}

void UTPSInputManager::OnReload()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->StartReload();
	}
}

void UTPSInputManager::SelectWeapon1()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->SelectWeapon1();
	}
}

void UTPSInputManager::SelectWeapon2()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->SelectWeapon2();
	}
}

void UTPSInputManager::SelectWeapon3()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->SelectWeapon3();
	}
}

void UTPSInputManager::UIToggle()
{
	if (Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
		PlayerCharacter->UIToggle();
	}
}
