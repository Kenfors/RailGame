// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RailgameInstance.generated.h"

/**
 * 
 */

UENUM()
 enum class EPlayingState : uint8 {
	 Menu,
	 Rail

};


UCLASS()
class RAILGAME_API URailgameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
		URailgameInstance(const FObjectInitializer& ObjectInitializer);
	



	EPlayingState PlayingState;

	void SetPlayingState(EPlayingState NewState);
	EPlayingState GetPlayingState();
	uint8 GetPlayingStateAsInt();
	
};
