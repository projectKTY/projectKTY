// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Player/PlayerCharacter.h"
#include "UI/HUD/PlayerHUDWidget.h"
#include "System/TPSInputManager.h"
#include "Kismet/GameplayStatics.h"

AShooterPlayerController::AShooterPlayerController()
{
	InputManager = CreateDefaultSubobject<UTPSInputManager>(TEXT("InputManager"));
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (!HasAuthority())
	{
		HUD->RemoveFromViewport();
		if (bIsWinner)
		{
			UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
			if (WinScreen != nullptr)
			{
				WinScreen->AddToViewport();
			}
		}
		else
		{
			UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
			if (LoseScreen != nullptr)
			{
				LoseScreen->AddToViewport();
			}
		}
		
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	}

}

void AShooterPlayerController::UpdateHUD(int32 CurrentAmmo, int32 Magazine)
{
	if (!IsLocalController())
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateHUD Called on Server! Skipping UI Update"));
		return;
	}

	if (HUD)
	{
		HUD->UpdateAmmoDisplay(CurrentAmmo, Magazine);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));
	}
}

UPlayerHUDWidget* AShooterPlayerController::GetHUD() const
{
	return HUD;
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
	}
		HUD = CreateWidget<UPlayerHUDWidget>(this, HUDClass);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("HUDWidget Successfully Added to Viewport"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to Create HUDWidget"));
		}
}
