// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Actors/FTeleport.h"
#include "GameFramework/GameModeBase.h"
#include "Support/Enums/FGameStatusEnum.h"

#include "FGameMode.generated.h"

UCLASS(minimalapi)
class AFGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFGameMode();

protected:
	FGameStatusEnum GameStatus;
	int PickedCounter;
	int PickedCollected;
	AFTeleport* Teleport;

	virtual void BeginPlay() override;

	void SetGameStatus(FGameStatusEnum CurrentGameStatus);
	void TogglePlayerInput(const bool Enable) const;
	void HandleGameStatus(FGameStatusEnum CurrentGameStatus);

	void Preparing();
	void Playing() const;
	void Complete() const;
	void Finished() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameStatusChange(FGameStatusEnum CurrentGameStatus);

public:
	void AddPickedCollected(const int Value);
	void SetPlayerOnTeleport();

	UFUNCTION(BlueprintCallable)
	FGameStatusEnum GetGameStatus() const;
	UFUNCTION(BlueprintCallable)
	int GetPickedCounter() const;
	UFUNCTION(BlueprintCallable)
	int GetPickedCollected() const;
};
