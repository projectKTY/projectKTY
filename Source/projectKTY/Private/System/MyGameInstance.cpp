// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MyGameInstance.h"
#include "Engine/DataTable.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> STATDATA(TEXT("/Script/Engine.DataTable'/Game/DataTable/uasset/Character.Character'"));
	if (STATDATA.Succeeded())
	{
		MyStatDatas = STATDATA.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> WEAPONDATA(TEXT("/Script/Engine.DataTable'/Game/DataTable/uasset/Weapon.Weapon'"));
	if (STATDATA.Succeeded())
	{
		WeaponDatas = WEAPONDATA.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
}

FMyCharacterData UMyGameInstance::GetStatData(FName NameID)
{
	FMyCharacterData* FoundRow = MyStatDatas->FindRow<FMyCharacterData>(NameID, TEXT("Get Character Stats"), true);

	if (FoundRow)
	{
		return *FoundRow;
	}

	return FMyCharacterData();
}

FWeaponData UMyGameInstance::GetWeaponData(FName NameID)
{
	FWeaponData* FoundRow = WeaponDatas->FindRow<FWeaponData>(NameID, TEXT("Get Weapon Data"), true);

	if (FoundRow)
	{
		return *FoundRow;
	}

	return FWeaponData();
}
