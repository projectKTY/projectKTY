// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_None			UMETA(DisplayName = "None"),
	EWT_AssaultRifle	UMETA(DisplayName = "Assault Rifle"),
	EWT_HandGun			UMETA(DisplayName = "HandGun"),
	EWT_SniperRifle		UMETA(DisplayName = "Sniper Rifle"),
	EWT_Shotgun			UMETA(DisplayName = "Shotgun")
};

class PROJECTKTY_API WeaponType
{
public:
	WeaponType();
	~WeaponType();
};
