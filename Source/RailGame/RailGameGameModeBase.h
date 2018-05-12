// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MenuWidget.h"
#include "Character/RailCharacter.h"
#include "GameFramework/GameMode.h"
#include "RailgameInstance.h"
#include "RailGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RAILGAME_API ARailGameGameModeBase : public AGameMode
{
	GENERATED_BODY()
public:

	ARailGameGameModeBase();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	bool bIsGameRunning = false;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void LaunchRail();

	UFUNCTION()
	void LaunchMainMenu();



	URailgameInstance* GetRailgameInstance();

	UPROPERTY()
	ARailCharacter* MainCharacter;
	UPROPERTY()
	APlayerController* MainController;


	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> MainMenuClass;
	UMenuWidget* MainMenuHUD;
};