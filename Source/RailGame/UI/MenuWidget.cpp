// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "RailGameGameModeBase.h"






void UMenuWidget::PlayButtonPressed()
{
	if (CurrentGameMode)
	{
		CurrentGameMode->StartGame();
	}


}
