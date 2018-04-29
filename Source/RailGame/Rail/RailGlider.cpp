// Fill out your copyright notice in the Description page of Project Settings.

#include "RailGlider.h"
#include "DrawDebugHelpers.h"


// Sets default values
ARailGlider::ARailGlider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = 200.f;
	VelocityMultiplier = 1.f;
	this->RootComponent = CreateDefaultSubobject< USceneComponent>(TEXT("DefaultSceneRoot")); RootComponent->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void ARailGlider::BeginPlay()
{
	Super::BeginPlay();
	
	ticker = 0.1f;
	CurrentCheckpointIndex = 0;
	CheckpointTarget = Checkpoints[CurrentCheckpointIndex];
}

// Called every frame
void ARailGlider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGameOver) return;

	ticker -= DeltaTime;
	if (ticker < 0) {
		DrawDebugSolidBox(GetWorld(), GetActorLocation(), FVector(10.f, 10.f, 20.f), FColor::Yellow, false, 2.f, 0);
		ticker = 0.1f;
	}

	CheckpointHandler();
	SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CheckpointTarget, DeltaTime, Velocity * VelocityMultiplier));
	
}

bool ARailGlider::CheckpointHandler()
{


	if (GetActorLocation().Equals(CheckpointTarget)) {
		if (CurrentCheckpointIndex < Checkpoints.Num()-1) {
			CurrentCheckpointIndex++;
			CheckpointTarget = Checkpoints[CurrentCheckpointIndex];
			UE_LOG(LogTemp, Log, TEXT("Current Checkpoint: %i"), CurrentCheckpointIndex);
		}
		else {
			bIsGameOver = true;
		}
	}

	return false;
}

