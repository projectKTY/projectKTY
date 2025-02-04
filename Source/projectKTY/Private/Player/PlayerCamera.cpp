// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UPlayerCamera::UPlayerCamera()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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

void UPlayerCamera::SetAttachmentToPlayer(APlayerCharacter* Player)
{
	 CameraBoom->SetupAttachment(Player->GetRootComponent());
	 CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	 CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	 FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	 FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}
