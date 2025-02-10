// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ARGun.h"

AARGun::AARGun()
{
	WeaponType = EWeaponType::EWT_AssaultRifle;
	MaxRange = 5000.0f;
	Damage = 10.0f;

	RecoilAmount = 2.0f;
	RecoilPattern = FVector2D(0.5f, 1.25f);
}
