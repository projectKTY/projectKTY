// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SniperGun.h"

ASniperGun::ASniperGun()
{
	WeaponType = EWeaponType::EWT_SniperRifle;
	MaxRange = 10000.0f;
	Damage = 80.0f;

	RecoilAmount = 5.0f;
	RecoilPattern = FVector2D(1.5f, 3.0f);
}
