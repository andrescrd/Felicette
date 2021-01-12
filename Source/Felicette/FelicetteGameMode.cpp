// Copyright Epic Games, Inc. All Rights Reserved.

#include "FelicetteGameMode.h"
#include "FelicettePlayerController.h"
#include "FelicetteCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFelicetteGameMode::AFelicetteGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFelicettePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}