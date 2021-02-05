// Fill out your copyright notice in the Description page of Project Settings.


#include "Support/Managers/FDataManager.h"

#include "Kismet/GameplayStatics.h"
#include "Support/Helpers/FSaveGame.h"

void AFDataManager::SaveLevels(const TArray<FLevelSetup> LevelsToSave)
{
	GetSaveGameInstance()->Levels = LevelsToSave;
	UGameplayStatics::SaveGameToSlot(GetSaveGameInstance(), "FSlotFelix", GetSaveGameInstance()->UserIndex);
}

TArray<FLevelSetup> AFDataManager::GetLevels()
{
	if (UFSaveGame* LoadedGame = Cast<UFSaveGame>(UGameplayStatics::LoadGameFromSlot("FSlotFelix", GetSaveGameInstance()->UserIndex)))
		return LoadedGame->Levels;

	TArray<FLevelSetup> Empty;
	return Empty;
}

void AFDataManager::ClearData()
{
	UGameplayStatics::DeleteGameInSlot("FSlotFelix", GetSaveGameInstance()->UserIndex);
}

class UFSaveGame* AFDataManager::GetSaveGameInstance()
{
	return IsValid(SaveGameInstance) ? SaveGameInstance : SaveGameInstance = Cast<UFSaveGame>(UGameplayStatics::CreateSaveGameObject(UFSaveGame::StaticClass()));
}
