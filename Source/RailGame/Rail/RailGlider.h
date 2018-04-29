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
	uint16 Velocity;

	float ticker;

	FVector CheckpointTarget;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Checkpoints")
	TArray<FVector> Checkpoints;
	uint8 CurrentCheckpointIndex;
	

	bool CheckpointHandler();
	

};
