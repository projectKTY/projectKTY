// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */

class UTPSInputManager;

UCLASS()
class PROJECTKTY_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShooterPlayerController();
	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;

	UTPSInputManager* InputManager;
};
