// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn/SpawnOverlapTrigger.h"
#include "Components/BoxComponent.h"
#include "Player/PlayerCharacter.h"

// Sets default values
ASpawnOverlapTrigger::ASpawnOverlapTrigger()
{
	SpawnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnTrigger"));
	SpawnTrigger->SetBoxExtent(FVector(775.0f, 775.0f, 250.0f));
	SpawnTrigger->SetupAttachment(RootComponent);
	SpawnTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASpawnOverlapTrigger::OnSpawnTriggerBeginOverlap);
}

void ASpawnOverlapTrigger::BeginPlay()
{
	Super::BeginPlay();
	TArray<TObjectPtr<AActor>> ChildActors;

	GetAttachedActors(ChildActors);
	for (AActor* Child : ChildActors)
	{
		FVector Location = Child->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Child Actor: %s %f %f %f"), *Child->GetName(), Location.X, Location.Y, Location.Z);
		Child->SetActorHiddenInGame(true);				
	}

	if (ManagedActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawner is not assigned "));
	}
}

void ASpawnOverlapTrigger::OnSpawnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		TArray<TObjectPtr<AActor>> ChildActors;

		GetAttachedActors(ChildActors);
		for (AActor* Child : ChildActors)
		{
			FVector Location = Child->GetActorLocation();
			FRotator Rotation = Child->GetActorRotation();
			if (GetWorld()->SpawnActor<ACharacter>(Child->GetClass(), Location, Rotation))
			{
				UE_LOG(LogTemp, Warning, TEXT("Create Success"));
			}			
		}
	}
}



