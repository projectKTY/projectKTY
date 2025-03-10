// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/PlayerHUDWidget.h"
#include "Components/TextBlock.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}

	if (!AmmoText)
	{
		UE_LOG(LogTemp, Error, TEXT("AmmoText Bind Failed"));
	}

	if (AmmoWarningText)
	{
		AmmoWarningText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerHUDWidget::UpdateAmmoDisplay(int32 CurrentAmmo, int32 Magazine)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateAmmoDisplay Method Call"));
	if (AmmoText)
	{
		FString AmmoString = FString::Printf(TEXT("%d / %d"), CurrentAmmo, Magazine);
		AmmoText->SetText(FText::FromString(AmmoString));
		UE_LOG(LogTemp, Warning, TEXT("AmmoText Update Successed"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AmmoText Update Failed"));
	}

	if (AmmoWarningText)
	{
		if (CurrentAmmo == 0)
		{
			AmmoWarningText->SetVisibility(ESlateVisibility::Visible);
			Crosshair->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			AmmoWarningText->SetVisibility(ESlateVisibility::Hidden);
			if (Crosshair->GetVisibility() == ESlateVisibility::Hidden)
			{
				Crosshair->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}
