// Fill out your copyright notice in the Description page of Project Settings.


#include "System/TPSInputManager.h"

void UTPSInputManager::Initialize(APlayerController* PlayerController, ATPSCharacter* ControlledCharacter)
{
	Character = ControlledCharacter;

	if (PlayerController)
	{
		auto* LocalPlayer = PlayerController->GetLocalPlayer();
		EnhancedInputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		if (EnhancedInputSubSystem && DefaultMappingContext)
		{
			EnhancedInputSubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void UTPSInputManager::BindInputActions(UEnhancedInputComponent* InputComponent)
{
	if (!InputComponent || !Character)
	{
		return;
	}

	InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UTPSInputManager::OnMove);
	InputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UTPSInputManager::OnLook);
}

void UTPSInputManager::OnMove(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->Move(Value.Get<float>());
	}
}

void UTPSInputManager::OnLook(const FInputActionValue& Value)
{
	if (Character)
	{
		Character->Look(Value.Get<float>());
	}
}
