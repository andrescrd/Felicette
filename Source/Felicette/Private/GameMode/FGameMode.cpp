// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/FGameMode.h"


#include "Character/FCharacter.h"
#include "GameFramework/SpectatorPawn.h"
#include "Player/FPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AFGameMode::AFGameMode()
{
	PlayerControllerClass = AFPlayerController::StaticClass();
	DefaultPawnClass = ASpectatorPawn::StaticClass();
}