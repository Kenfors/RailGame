// Fill out your copyright notice in the Description page of Project Settings.

#include "RailGameGameModeBase.h"
#include "RailGame.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "GameFramework/SpectatorPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>


ARailGameGameModeBase::ARailGameGameModeBase()
{

	static ConstructorHelpers::FObjectFinder<UClass> PlayerBPClassQuery(TEXT("Blueprint'/Game/Character/CBP_Character.CBP_Character_C'"));
	if (PlayerBPClassQuery.Succeeded()){
		DefaultPawnClass = PlayerBPClassQuery.Object;

	}
	
	ConstructorHelpers::FObjectFinder<UClass> MainMenuQuery(TEXT("WidgetBlueprint'/Game/UI/MainMenu.MainMenu_C'"));
	if (MainMenuQuery.Succeeded()){
		MainMenuClass = MainMenuQuery.Object;

	}
	
	bPauseable = true;
	bStartPlayersAsSpectators = true;

	PlayerControllerClass = APlayerController::StaticClass();
	SpectatorClass = ASpectatorPawn::StaticClass();
	
	

}

void ARailGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();


}


void ARailGameGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	MainController = NewPlayer;
	EPlayingState CurrentState = GetRailgameInstance()->GetPlayingState();

	switch (CurrentState)
	{
	case EPlayingState::Menu:
		LaunchMainMenu();
		break;
	case EPlayingState::Rail:
		LaunchRail();
		break;
	default:
		break;
	}


}

void ARailGameGameModeBase::StartGame()
{
	GetRailgameInstance()->SetPlayingState(EPlayingState::Rail);
	MainMenuHUD->RemoveFromViewport();

	UGameplayStatics::OpenLevel(GetWorld(), FName("DEBUG"));
	RestartPlayerAtPlayerStart(MainController, FindPlayerStart(MainController));
	MainController->bShowMouseCursor = false;
	
}

void ARailGameGameModeBase::LaunchRail()
{


}

void ARailGameGameModeBase::LaunchMainMenu()
{
	MainMenuHUD = CreateWidget<UMenuWidget>(MainController, MainMenuClass);
	if (MainMenuHUD) {
		MainMenuHUD->CurrentGameMode = this;
		MainMenuHUD->AddToViewport();
		MainController->bShowMouseCursor = true;
	}
}


URailgameInstance* ARailGameGameModeBase::GetRailgameInstance()
{
	return Cast<URailgameInstance>(GetGameInstance());
}
