// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RailGlider.generated.h"

UCLASS()
class RAILGAME_API ARailGlider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARailGlider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool bIsGameOver = false;

	uint8 VelocityMultiplier;
	UPROPERTY(EditAnywhere, Category = "F&K Gameplay")
	uint16 Velocity;
	UPROPERTY(EditAnywhere, Category = "F&K Gameplay")
	bool DoDrawIngameDebugPath = false;

	bool bHasPlayerAttached = false;

	float ticker;

	FVector CheckpointTarget;
	UPROPERTY(EditAnywhere, Category = "F&K Checkpoints")
	TArray<FVector> Checkpoints;
	uint8 CurrentCheckpointIndex;


	UPROPERTY(EditAnywhere, Category = "F&K Checkpoints")
	bool DoDrawDebugLines = false;

	void AttachPlayer(APawn* AttachingPawn);
	void DetachPlayer();

	class ARailCharacter* MainCharacter;

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	bool CheckpointHandler();
	

};
