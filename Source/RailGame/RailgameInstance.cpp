// Fill out your copyright notice in the Description page of Project Settings.

#include "RailgameInstance.h"

URailgameInstance::URailgameInstance(const FObjectInitializer & ObjectInitializer)
{


	PlayingState = EPlayingState::Menu;
}

void URailgameInstance::SetPlayingState(EPlayingState NewState)
{
	PlayingState = NewState;
}

EPlayingState URailgameInstance::GetPlayingState()
{
	return PlayingState;
}

uint8 URailgameInstance::GetPlayingStateAsInt()
{
	switch (PlayingState)
	{
	case EPlayingState::Menu:
		return 0;
		break;
	case EPlayingState::Rail:
		return 1;
		break;
	default:
		return -1;
		break;
	}


}
