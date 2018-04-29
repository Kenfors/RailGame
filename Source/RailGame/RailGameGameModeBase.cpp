// Fill out your copyright notice in the Description page of Project Settings.

#include "RailGameGameModeBase.h"
#include "RailGame.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ARailGameGameModeBase::ARailGameGameModeBase()
{

	bPauseable = true;
	PlayerControllerClass = APlayerController::StaticClass();
	
	static ConstructorHelpers::FObjectFinder<UClass> PlayerBPClassQuery(TEXT("Blueprint'/Game/Character/CBP_Character.CBP_Character_C'"));

	if (PlayerBPClassQuery.Succeeded())
	{
		DefaultPawnClass = PlayerBPClassQuery.Object;

	}

}
/*
APawn * ARailGameGameModeBase::SpawnDefaultPawnFor(AController * NewPlayer, AActor * StartSpot)
{
	return nullptr;
}
*/