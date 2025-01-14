// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomDataTables.h"
#include "CharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTKTY_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetMaxHp() const { return Maxhp; }
	int32 GetAttack() const { return Attack; }

protected:
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	FString NameID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Maxhp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	float Movespeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Crit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Critd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	FString Weaponinit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Upmaxhp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Upattack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Updefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	float Upmovespeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Upcrit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Upcritd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	int32 Upexp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	FString Bone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	FString Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStat", meta = (AllowPrivateAccess = true))
	FString Animset;

private:
	void SetStat();
};
