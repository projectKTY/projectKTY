// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/TPSCharacter.h"
#include "TPSInputManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTKTY_API UTPSInputManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(class APlayerController* PlayerController, ATPSCharacter* ControlledCharacter);
	void BindInputActions(class UEnhancedInputComponent* InputComponent);

protected:
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);

private:

	ATPSCharacter* Character;

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubSystem;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;
};
