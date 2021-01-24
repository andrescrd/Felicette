// Fill out your copyright notice in the Description page of Project Settings.


#include "Support/Managers/FDataManager.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Support/Helpers/FSaveGame.h"

void AFDataManager::SaveLevels(const TArray<FLevelSetup> LevelsToSave)
{
	GetSaveGameInstance()->Levels = LevelsToSave;
	UGameplayStatics::SaveGameToSlot(GetSaveGameInstance(), GetSaveGameInstance()->SaveSlotName, GetSaveGameInstance()->UserIndex);
}

TArray<FLevelSetup> AFDataManager::GetLevels()
{
	if (UFSaveGame *LoadedGame = Cast<UFSaveGame>(UGameplayStatics::LoadGameFromSlot(GetSaveGameInstance()->SaveSlotName, GetSaveGameInstance()->UserIndex)))
	{
		GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, FString::Printf(TEXT("Game Loaded")));
		return LoadedGame->Levels;
	}

	TArray<FLevelSetup> Empty;
	return Empty;
}

void AFDataManager::ClearData()
{
	GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, FString::Printf(TEXT("Clear Data")));
}
class UFSaveGame *AFDataManager::GetSaveGameInstance()
{
	return IsValid(SaveGameInstance) ? SaveGameInstance : SaveGameInstance = Cast<UFSaveGame>(UGameplayStatics::CreateSaveGameObject(UFSaveGame::StaticClass()));
}