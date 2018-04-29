// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RailCharacter.generated.h"

UCLASS()
class RAILGAME_API ARailCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARailCharacter(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere)
		class USpringArmComponent*  CameraBoom;

	UPROPERTY(EditAnywhere)
		class UCameraComponent*  ViewCamera;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetupRailFollower(class ARailGlider Rail);

	class ARailGlider* RailGlider;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveUp(const float Value);
	void MoveRight(const float Value);
	
	
};
