// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class PROJECTKTY_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateAmmoDisplay(int32 CurrentAmmo, int32 Magazine);

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "TEXT", meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* AmmoText;
};
