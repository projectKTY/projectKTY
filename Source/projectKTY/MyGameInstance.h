// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomDataTables.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTKTY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	FMyCharacterData GetStatData(FName NameID);

private:
	UPROPERTY()
	class UDataTable* MyStatDatas;
};