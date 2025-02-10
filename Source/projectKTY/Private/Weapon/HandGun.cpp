// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HandGun.h"

AHandGun::AHandGun()
{
	WeaponType = EWeaponType::EWT_HandGun;
	MaxRange = 5000.0f;
	Damage = 15.0f;

	RecoilAmount = 3.0f;
	RecoilPattern = FVector2D(0.7f, 1.5f);
}
