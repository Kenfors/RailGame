// Fill out your copyright notice in the Description page of Project Settings.

#include "RailCharacter.h"
#include "RailGame.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "RailGame/Rail/RailGlider.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


// Sets default values
ARailCharacter::ARailCharacter(const FObjectInitializer& ObjectInitializer)
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("Camera Boom"));
	ViewCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Top Down Camera"));

	
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->TargetArmLength = 200;
	CameraBoom->TargetOffset.Set(0.f, 0.f, 750.f);
	CameraBoom->bAbsoluteRotation = true;

	ViewCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	ViewCamera->SetRelativeRotation(FRotator(-62.f, 0.f, 0.f));     //Make camera look at center of hero (aprox).
	ViewCamera->bUsePawnControlRotation = false;
	ViewCamera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
	ViewCamera->PostProcessSettings.AutoExposureMaxBrightness = FMath::Exp2(1);
	ViewCamera->PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
	ViewCamera->PostProcessSettings.AutoExposureMinBrightness = FMath::Exp2(1);



	


}

// Called when the game starts or when spawned
void ARailCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARailCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARailCharacter::SetupRailFollower(ARailGlider Rail)
{
}

// Called to bind functionality to input
void ARailCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &ARailCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARailCharacter::MoveRight);

}

void ARailCharacter::MoveUp(const float Value)
{
	AddMovementInput(GetActorUpVector(), Value);

}

void ARailCharacter::MoveRight(const float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

