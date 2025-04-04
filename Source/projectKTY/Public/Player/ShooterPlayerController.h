// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/TPSInputManager.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */

class UPlayerHUDWidget;
class UTPSInputManager;

UCLASS()
class PROJECTKTY_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShooterPlayerController();
	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;

	void UpdateHUD(int32 CurrentAmmo, int32 Magazine);

	void ToggleCursorMode();

	UPlayerHUDWidget* GetHUD() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerHUDWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	UPlayerHUDWidget* HUD;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UTPSInputManager* InputManager;
};
