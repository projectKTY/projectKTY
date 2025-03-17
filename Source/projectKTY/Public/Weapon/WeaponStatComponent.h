// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTKTY_API UWeaponStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) FString GetNameID() const { return NameID; }
	UFUNCTION(BlueprintCallable) FString GetType() const { return Type; }
	UFUNCTION(BlueprintCallable) int32 GetMaxHp() const { return Maxhp; }
	UFUNCTION(BlueprintCallable) int32 GetAttack() const { return Attack; }
	UFUNCTION(BlueprintCallable) int32 GetDefence() const { return Defence; }
	UFUNCTION(BlueprintCallable) float GetSpeed() const { return Movespeed; }
	UFUNCTION(BlueprintCallable) int32 GetMagazine() const { return Magazine; }
	UFUNCTION(BlueprintCallable) float GetAccuracy() const { return Accuracy; }
	UFUNCTION(BlueprintCallable) float GetRebound() const { return Rebound; }
	UFUNCTION(BlueprintCallable) float GetAttackSpeed() const { return AttackSpeed; }
	UFUNCTION(BlueprintCallable) float GetReloadtime() const { return Reloadtime; }

protected:
	UPROPERTY(EditAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	FString NameID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	int32 Maxhp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	int32 Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	float Movespeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	int32 Crit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	int32 Critd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	float Accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	float Rebound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	int32 Magazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	float Reloadtime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	FString Skillshoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	FString Skill1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat", meta = (AllowPrivateAccess = true))
	FString Skill2;

private:
	void SetStat();
};
