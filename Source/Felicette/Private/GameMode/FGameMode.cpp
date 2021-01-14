// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/FGameMode.h"

#include "Player/FPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AFGameMode::AFGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}