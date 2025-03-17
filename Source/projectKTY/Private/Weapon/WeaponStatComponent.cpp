// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponStatComponent.h"
#include "System/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWeaponStatComponent::UWeaponStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UWeaponStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetStat();
}


// Called every frame
void UWeaponStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponStatComponent::SetStat()
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		FWeaponData WeaponData = MyGameInstance->GetWeaponData(FName(*NameID));

		Type = WeaponData.Type;
		Maxhp = WeaponData.Maxhp;
		Attack = WeaponData.Attack;
		Defence = WeaponData.Defence;
		Movespeed = WeaponData.Movespeed;
		Crit = WeaponData.Crit;
		Critd = WeaponData.Critd;
		Accuracy = WeaponData.Accuracy;
		Rebound = WeaponData.Rebound;
		AttackSpeed = WeaponData.AttackSpeed;
		Magazine = WeaponData.Magazine;
		Reloadtime = WeaponData.Reloadtime;
		Skillshoot = WeaponData.Skillshoot;
		Skill1 = WeaponData.Skill1;
		Skill2 = WeaponData.Skill2;
	}
}

