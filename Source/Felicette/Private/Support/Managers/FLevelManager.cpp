#include "Support/Managers/FLevelManager.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/LevelStreaming.h"
#include "Support/Structs/FLevelSetup.h"

TArray<FLevelSetup> AFLevelManager::GetGameplayLevels() const { return GameplayLevels; }

void AFLevelManager::SetGameplayLevels(const TArray<FLevelSetup> NewLevels) { GameplayLevels = NewLevels; }

FLevelSetup AFLevelManager::GetNextGameplayLevel()
{
	FLevelSetup Level;

	for (int32 Index = 0; Index < GameplayLevels.Num(); Index++)
	{
		if (GameplayLevels[Index].LevelName.IsEqual(LastLevelLoaded))
		{
			Level = (Index + 1 == GameplayLevels.Num()) ? End : GameplayLevels[Index + 1];
			break;
		}
	}

	return Level;
}

void AFLevelManager::LoadNextGameplayLevel(UWorld* World)
{
	const FLevelSetup NextGameplayLevel = GetNextGameplayLevel();

	if (NextGameplayLevel.LevelName == Menu.LevelName)
	{
		LoadMenuLevel(World);
	}
	else if (NextGameplayLevel.LevelName == End.LevelName)
	{
		LoadEndLevel(World);
	}
	else
	{
		const int32 Index = GameplayLevels.FindLastByPredicate([NextGameplayLevel](const FLevelSetup LevelSetup)
		{
			return LevelSetup.LevelName == NextGameplayLevel.LevelName;
		});

		if (Index != INDEX_NONE)
		{
			GameplayLevels[Index].State = FLevelStateEnum::Unlocked;
			LoadGameplayLevel(World, NextGameplayLevel.LevelName);
		}
	}
}

void AFLevelManager::LoadMenuLevel(UWorld* Context)
{
	LastLevelLoaded = FLevelSetup().LevelName;
	UGameplayStatics::OpenLevel(Context, Menu.LevelName);
}

void AFLevelManager::LoadEndLevel(UWorld* Context)
{
	LastLevelLoaded = FLevelSetup().LevelName;
	UGameplayStatics::OpenLevel(Context, End.LevelName);
}

void AFLevelManager::LoadGameplayLevel(UWorld* World, const FName MapName)
{
	if (LoadingWidgetClass)
	{
		if (!CurrentWidget)
			CurrentWidget = CreateWidget<UUserWidget>(World, LoadingWidgetClass);

		CurrentWidget->AddToViewport();

		if (LastLevelLoaded.GetStringLength() > 0 && LastLevelLoaded != FLevelSetup().LevelName)
		{
			ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(World, LastLevelLoaded);
			LevelStreaming->SetShouldBeVisible(false);
			LevelStreaming->SetIsRequestingUnloadAndRemoval(true);
		}

		FTimerHandle UniqueHandle;
		const FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &AFLevelManager::PreparingLevel, World, MapName);
		World->GetTimerManager().SetTimer(UniqueHandle, RespawnDelegate, 3, false);
	}
}

void AFLevelManager::Restart(UWorld* Context)
{
	LastLevelLoaded = FLevelSetup().LevelName;
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(Context);
	UGameplayStatics::OpenLevel(Context, *LevelName);
}

void AFLevelManager::PreparingLevel(UWorld* World, FName Map)
{
	const FLatentActionInfo Info;
	UGameplayStatics::LoadStreamLevel(World, Map, true, true, Info);
		
	LastLevelLoaded = Map;

	FTimerHandle UniqueHandle;
	World->GetTimerManager().SetTimer(UniqueHandle, this, &AFLevelManager::OnMapLoaded, 3, false);
}

void AFLevelManager::OnMapLoaded()
{
	FOnMapLoaded.Broadcast();

	if (CurrentWidget)
		CurrentWidget->RemoveFromViewport();
}
