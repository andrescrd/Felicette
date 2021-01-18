// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/FGameMode.h"


#include "Actors/FPickup.h"
#include "GameStates/FGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPlayerController.h"

AFGameMode::AFGameMode()
{
	GameStatus = FGameStatusEnum::UNDEFINED;
	GameStateClass = AFGameState::StaticClass();
	PlayerControllerClass = AFPlayerController::StaticClass();
}

void AFGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetGameStatus(FGameStatusEnum::PREPARING);
}

FGameStatusEnum AFGameMode::GetGameStatus() const { return GameStatus; }

int AFGameMode::GetPickedCounter() const { return PickedCounter; }

int AFGameMode::GetPickedCollected() const { return PickedCollected; }

void AFGameMode::AddPickedCollected(const int Value)
{
	PickedCollected += Value;

	if (PickedCounter == PickedCollected)
		SetGameStatus(FGameStatusEnum::FINISH);
}

void AFGameMode::SetGameStatus(const FGameStatusEnum CurrentGameStatus)
{
	if (CurrentGameStatus == GameStatus)
		return;

	GameStatus = CurrentGameStatus;
	HandleGameStatus(GameStatus);
	OnGameStatusChange(GameStatus);
}

void AFGameMode::Preparing()
{
	TogglePlayerInput(false);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFPickup::StaticClass(), OutActors);
	PickedCounter = OutActors.Num();

	SetGameStatus(FGameStatusEnum::PLAYING);
}

void AFGameMode::Playing() { TogglePlayerInput(true); }

void AFGameMode::Finished() { TogglePlayerInput(false); }

void AFGameMode::TogglePlayerInput(const bool Enable) const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (AFPlayerController* PlayerController = Cast<AFPlayerController>(PC))
		PlayerController->ToggleInput(Enable);
}

void AFGameMode::HandleGameStatus(const FGameStatusEnum CurrentGameStatus)
{
	switch (CurrentGameStatus)
	{
	case FGameStatusEnum::PREPARING:
		Preparing();
		break;
	case FGameStatusEnum::PLAYING:
		Playing();
		break;
	case FGameStatusEnum::FINISH:
		Finished();
		break;
	default:
		break;
	}
}
