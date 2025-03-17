// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CustomDataTables.generated.h"

USTRUCT(BlueprintType)
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Maxhp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Movespeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Crit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Critd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Weaponinit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Upmaxhp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Upattack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Updefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Upmovespeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Upcrit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Upcritd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 Upexp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Bone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Animset;
};


USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Maxhp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Movespeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Crit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Critd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Rebound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Reloadtime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString Skillshoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString Skill1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString Skill2;
};


UCLASS()
class PROJECTKTY_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomDataTables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
