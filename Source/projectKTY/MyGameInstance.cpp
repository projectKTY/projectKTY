// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/DataTable.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> STATDATA(TEXT("/Script/Engine.DataTable'/Game/DataTable/uasset/Character.Character'"));
	if (STATDATA.Succeeded())
	{
		MyStatDatas = STATDATA.Object;
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
