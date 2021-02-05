// Copyright Epic Games, Inc. All Rights Reserved.

#include "World/GameModes/FGameMode.h"


#include "EngineUtils.h"
#include "Actors/FPickup.h"
#include "Actors/FTeleport.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPlayerController.h"
#include "World/GameInstances/FGameInstance.h"
#include "World/GameStates/FGameState.h"
#include "TimerManager.h"

AFGameMode::AFGameMode()
{
	GameStatus = FGameStatusEnum::UNDEFINED;
	GameStateClass = AFGameState::StaticClass();
	PlayerControllerClass = AFPlayerController::StaticClass();
}

void AFGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GameInstanceRef))
		GameInstanceRef = GetGameInstance<UFGameInstance>();

	GameInstanceRef->OnGameplayMapLoaded.AddDynamic(this, &AFGameMode::HandleOnGameplayMapLoaded);
	GameInstanceRef->LoadLastLevel(GetWorld());
}

FGameStatusEnum AFGameMode::GetGameStatus() const { return GameStatus; }

int AFGameMode::GetPickedCounter() const { return PickedCounter; }

int AFGameMode::GetPickedCollected() const { return PickedCollected; }

void AFGameMode::HandleOnGameplayMapLoaded() { SetGameStatus(FGameStatusEnum::PREPARING); }

void AFGameMode::HandleOnFinish() { GetGameInstance<UFGameInstance>()->LoadNextGameplayLevel(GetWorld()); }//used as delay while change map 

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
	PickedCounter = 0;
	PickedCollected = 0;
	Teleport = nullptr;
	
	TArray<AActor*> PickupActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPickup::StaticClass(), PickupActors);
	PickedCounter = PickupActors.Num();
	
	TArray<AActor*> TeleportActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFTeleport::StaticClass(), TeleportActors);

	if(TeleportActors.Num() > 0)
		Teleport = Cast<AFTeleport>(TeleportActors[0]);

	TogglePlayerInput(false);
	SetGameStatus(FGameStatusEnum::PLAYING);
}

void AFGameMode::Playing() const { TogglePlayerInput(true); }

void AFGameMode::Complete() const { Teleport->SetIsActivated(true); }

void AFGameMode::Finished() 
{
	TogglePlayerInput(false);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFGameMode::HandleOnFinish, 2, false);	
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
