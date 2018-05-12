// Fill out your copyright notice in the Description page of Project Settings.

#include "RailGlider.h"
#include "Character/RailCharacter.h"
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
	if (!bHasPlayerAttached) return;

	ticker -= DeltaTime;
	if (ticker < 0) {
		if (DoDrawIngameDebugPath)
		{
			DrawDebugSolidBox(GetWorld(), GetActorLocation(), FVector(10.f, 10.f, 20.f), FColor::Yellow, false, 2.f, 0);
		}
		ticker = 0.1f;
	}

	CheckpointHandler();
	SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CheckpointTarget, DeltaTime, Velocity * VelocityMultiplier));
	
}

void ARailGlider::AttachPlayer(APawn * AttachingPawn)
{
	if (!AttachingPawn) return;

	bHasPlayerAttached = true;
	MainCharacter = Cast<ARailCharacter>(AttachingPawn);

}

void ARailGlider::DetachPlayer()
{
	bHasPlayerAttached = false;
}

void ARailGlider::OnConstruction(const FTransform & Transform)
{
	if (!GIsEditor) return;

	UE_LOG(LogTemp, Log, TEXT("Constructing...."));
	if (!GetWorld()) return;
	
	FlushPersistentDebugLines(GetWorld());

	if (DoDrawDebugLines)
	{
		//DrawDebugSolidBox(GetWorld(), this->GetActorLocation(), FVector(1000, 1000, 1000), FColor::Red, true, -1.f, 0);

		for (uint8 i = 1; i < Checkpoints.Num(); i++)
		{
			DrawDebugLine(GetWorld(), Checkpoints[i - 1], Checkpoints[i], FColor::Red, true, -1.f, 0, 20.f);

		}
	}

	

}

void ARailGlider::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property == nullptr) return;

	FName name = PropertyChangedEvent.Property->GetFName();

	UE_LOG(LogTemp, Log, TEXT("Post Changed:... %s"), *name.ToString());
	UE_LOG(LogTemp, Log, TEXT("Post Index:... %i"), PropertyChangedEvent.GetArrayIndex(name.ToString()));

	if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd)
	{
		int index = PropertyChangedEvent.GetArrayIndex(name.ToString());
		if (index == -1) return;
		UE_LOG(LogTemp, Log, TEXT("Added checkpoint to array..."));
	}


	Super::PostEditChangeProperty(PropertyChangedEvent);
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

