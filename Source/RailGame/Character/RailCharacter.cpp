// Fill out your copyright notice in the Description page of Project Settings.

#include "RailCharacter.h"
#include "RailGame.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "RailGame/Rail/RailGlider.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
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
	CameraBoom->TargetArmLength = 500;
	CameraBoom->TargetOffset.Set(0.f, 0.f, 200.f);
	CameraBoom->bAbsoluteRotation = false;
	

	ViewCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	ViewCamera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));     //Make camera look at center of hero (aprox).
	ViewCamera->bUsePawnControlRotation = false;
	ViewCamera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
	ViewCamera->PostProcessSettings.AutoExposureMaxBrightness = FMath::Exp2(1);
	ViewCamera->PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
	ViewCamera->PostProcessSettings.AutoExposureMinBrightness = FMath::Exp2(1);



	


}

void ARailCharacter::FindRail()
{
	TSubclassOf<ARailGlider> ClassToFind;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARailGlider::StaticClass(), FoundActors);

	UE_LOG(LogTemp, Log, TEXT("Found actors: %i"), FoundActors.Num());
	if (!(FoundActors.Num() > 0)) return;

	//UE_LOG(LogTemp, Log, TEXT("Found actors: %i"), FoundActors.Num());
	
	RailGlider = Cast<ARailGlider>(FoundActors[0]);

	AttachToRail();
}

void ARailCharacter::AttachToRail()
{
	if (!RailGlider) return;
	UE_LOG(LogTemp, Log, TEXT("CheckpointLocation:"));
	RailGlider->bHasPlayerAttached = true;


}

// Called when the game starts or when spawned
void ARailCharacter::BeginPlay()
{
	Super::BeginPlay();

	FindRail();
	
}







// Called every frame
void ARailCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RailGlider) {
		if (RailGlider->bHasPlayerAttached)
		{
			MoveToRail(DeltaTime);
			MoveToAxis(DeltaTime);
		}
	}
	else
	{
		FindRail();
	}

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

void ARailCharacter::MoveToRail(const float DeltaTime)
{
	if (!RailGlider) return;
	//FVector Dir = FMath::VInterpTo(oldDir, RailGlider->CheckpointTarget - this->GetActorLocation(), DeltaTime, 1);
	FVector Dir = RailGlider->CheckpointTarget - this->GetActorLocation();
	oldDir = Dir;
	//this->SetActorRotation();
	GetController()->SetControlRotation(FMath::RInterpTo(GetActorRotation(), Dir.Rotation(), DeltaTime, 5.f));

	DrawDebugLine(GetWorld(), this->GetActorLocation(), RailGlider->CheckpointTarget, FColor::Green, false, -1.f, 0, 20.f);
	

	AddMovementInput(GetControlRotation().Vector(), 0.2);
}

void ARailCharacter::MoveToAxis(float DeltaTime)
{
	FVector Distance = FVector();
	Distance.Z = GetActorLocation().Z;
	Distance *= -1;

	AddMovementInput(FMath::VInterpTo(oldZDir, Distance, DeltaTime, 2));

}

