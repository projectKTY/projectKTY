// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySoldierType.h"
#include "Character/WeaponManager.h"

void AEnemySoldierType::Attack_Shot()
{
	if (WeaponManager != nullptr)
	{
		if (WeaponManager->HasGun())
		{
			WeaponManager->GunFire();
		}
	}
}
