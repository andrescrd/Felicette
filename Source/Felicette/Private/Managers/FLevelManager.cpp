// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/FLevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

TArray<FLevelSetup> AFLevelManager::GetGameplayLevels() const { return GameplayLevels; }

void AFLevelManager::SetGameplayLevels(const TArray<FLevelSetup> NewLevels) { GameplayLevels = NewLevels; }

FLevelSetup AFLevelManager::GetNextGameplayLevel(UObject* Context)
{
	const FName CurrentLevelName = CleanLevelString(Context);
	FLevelSetup Level;

	for (int32 Index = 0; Index < GameplayLevels.Num(); Index++)
	{
		if (GameplayLevels[Index].LevelName.IsEqual(CurrentLevelName))
		{
			Level = (Index + 1 == GameplayLevels.Num()) ? Menu : GameplayLevels[Index + 1];
			break;
		}
	}

	return Level;
}

void AFLevelManager::LoadNextGameplayLevel(UObject* Context)
{
	const FLevelSetup NextGameplayLevel = GetNextGameplayLevel(Context);
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);

	for (int32 Index = 0; Index < GameplayLevels.Num(); Index++)
	{
		if (NextGameplayLevel.LevelName.IsEqual(GameplayLevels[Index].LevelName))
		{
			GameplayLevels[Index].State = FLevelStateEnum::Unlocked;
			UGameplayStatics::OpenLevel(World, NextGameplayLevel.LevelName);
			break;
		}
	}
}

void AFLevelManager::LoadLevel(UObject* Context, const FName LevelNameToLoad)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	UE_LOG(LogTemp, Warning, TEXT("Level to load %s"), *LevelNameToLoad.ToString());
	UGameplayStatics::OpenLevel(World, LevelNameToLoad, true);
}

FName AFLevelManager::CleanLevelString(UObject* Context)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	const FString Prefix = World->StreamingLevelsPrefix;
	const FString LevelName = World->GetMapName();
	return FName(*LevelName.RightChop(Prefix.Len()));
}
