// Fill out your copyright notice in the Description page of Project Settings.


#include "Support/Managers/FDataManager.h"
#include "Kismet/GameplayStatics.h"
#include "Support/Helpers/FSaveGame.h"

const FString SlotName = "FSlotFelix";

void AFDataManager::SaveLevels(const TArray<FLevelSetup> LevelsToSave)
{
	GetSaveGameInstance()->Levels = LevelsToSave;
	UGameplayStatics::SaveGameToSlot(GetSaveGameInstance(), SlotName, GetSaveGameInstance()->UserIndex);
}

TArray<FLevelSetup> AFDataManager::GetLevels()
{
	if (UFSaveGame* LoadedGame = Cast<UFSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, GetSaveGameInstance()->UserIndex)))
		return LoadedGame->Levels;

	TArray<FLevelSetup> Empty;
	return Empty;
}

void AFDataManager::ClearData() { UGameplayStatics::DeleteGameInSlot(SlotName, GetSaveGameInstance()->UserIndex); }

class UFSaveGame* AFDataManager::GetSaveGameInstance()
{
	return IsValid(SaveGameInstance) ? SaveGameInstance : SaveGameInstance = Cast<UFSaveGame>(UGameplayStatics::CreateSaveGameObject(UFSaveGame::StaticClass()));
}
