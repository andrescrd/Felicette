// Copyright Epic Games, Inc. All Rights Reserved.

#include "World/GameModes/FGameMode.h"

#include "Actors/FPickup.h"
#include "Actors/FTeleport.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPlayerController.h"
#include "World/GameInstances/FGameInstance.h"
#include "World/GameStates/FGameState.h"

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
		SetGameStatus(FGameStatusEnum::COMPLETE);
}

void AFGameMode::SetPlayerOnTeleport() { SetGameStatus(FGameStatusEnum::FINISH); }

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

	TArray<AActor*> PickupActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFPickup::StaticClass(), PickupActors);
	PickedCounter = PickupActors.Num();

	AActor* Actor = UGameplayStatics::GetActorOfClass(this, AFTeleport::StaticClass());

	if (Actor)
		Teleport = Cast<AFTeleport>(Actor);

	SetGameStatus(FGameStatusEnum::PLAYING);
}

void AFGameMode::Playing() const { TogglePlayerInput(true); }

void AFGameMode::Complete() const { Teleport->SetIsActivated(true); }

void AFGameMode::Finished() const
{
	TogglePlayerInput(false);	
	Cast<UFGameInstance>(GetGameInstance())->LoadNextGameplayLevel(GetWorld());
}

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
	case FGameStatusEnum::COMPLETE:
		Complete();
		break;
	case FGameStatusEnum::FINISH:
		Finished();
		break;
	default:
		break;
	}
}
