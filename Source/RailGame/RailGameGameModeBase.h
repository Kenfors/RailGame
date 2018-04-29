// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RailCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "RailGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RAILGAME_API ARailGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	ARailGameGameModeBase();


	//UFUNCTION(BlueprintNativeEvent, Category = Game)
	//APawn* SpawnDefaultPawnFor(AController* NewPlayer, AActor* StartSpot);
};
