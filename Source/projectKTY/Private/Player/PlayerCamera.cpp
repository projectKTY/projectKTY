// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UPlayerCamera::UPlayerCamera()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	RegisterComponent();
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// CameraBoom->SetupAttachment(Player->GetRootComponent());
	// CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	// CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	// FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void UPlayerCamera::ZoomIn()
{
	bIsZoomedIn = true;
}

void UPlayerCamera::ZoomOut()
{
	bIsZoomedIn = false;
}

void UPlayerCamera::SetAttachmentToPlayer(APlayerCharacter* Player)
{
	 CameraBoom->SetupAttachment(Player->GetRootComponent());
	 CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	 CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	 FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	 FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	 DefaultFOV = 90.0f;
	 ZoomedFOV = 60.0f;
	 ZoomInterpSpeed = 10.0f;
	 bIsZoomedIn = false;

	 FollowCamera->SetFieldOfView(DefaultFOV);
}

void UPlayerCamera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float TargetFOV = bIsZoomedIn ? ZoomedFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(FollowCamera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	FollowCamera->SetFieldOfView(NewFOV);
}