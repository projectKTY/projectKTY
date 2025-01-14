// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	Level = 1;
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// UE_LOG(LogTemp, Warning, TEXT("Character Stat: %d"), GetStatData(1)->Attack);
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetStat();
}


// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterStatComponent::SetStat()
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		FMyCharacterData StatData = MyGameInstance->GetStatData(FName(*NameID));
		
		Type = StatData.Type;
		Maxhp = StatData.Maxhp;
		Attack = StatData.Attack;
		Defence = StatData.Defence;
		Movespeed = StatData.Movespeed;
		Crit = StatData.Crit;
		Critd = StatData.Critd;
		Exp = StatData.Exp;
		Weaponinit = StatData.Weaponinit;
		
		Upmaxhp = StatData.Upmaxhp;
		Upattack = StatData.Upattack;
		Updefence = StatData.Updefence;
		Upmovespeed = StatData.Upmovespeed;
		Upexp = StatData.Upexp;

		Bone = StatData.Bone;
		Model = StatData.Model;
		Animset = StatData.Animset;
	}
}


