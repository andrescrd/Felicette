// Fill out your copyright notice in the Description page of Project Settings.


#include "Support/Managers/FLevelManager.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Support/Structs/FLevelSetup.h"

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

	if (NextGameplayLevel.LevelName == Menu.LevelName)
	{
		LoadMenuLevel(Context);
	}
	else
	{
		for (int32 Index = 0; Index < GameplayLevels.Num(); Index++)
		{
			if (NextGameplayLevel.LevelName.IsEqual(GameplayLevels[Index].LevelName))
			{
				GameplayLevels[Index].State = FLevelStateEnum::Unlocked;
				LoadMap(World, NextGameplayLevel.LevelName);
				break;
			}
		}
	}
}

void AFLevelManager::LoadMenuLevel(UObject* Context) { LoadLevel(Context, Menu.LevelName); }

void AFLevelManager::LoadLevel(UObject* Context, const FName LevelNameToLoad)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	UE_LOG(LogTemp, Warning, TEXT("Level to load %s"), *LevelNameToLoad.ToString());
	LoadMap(World, LevelNameToLoad);
}


void AFLevelManager::LoadMap(UWorld* World, const FName MapName)
{
	if (LoadingWidgetClass)
	{
		auto CurrentWidget = CreateWidget<UUserWidget>(World, LoadingWidgetClass);

		if (CurrentWidget != nullptr)
			CurrentWidget->AddToViewport();

		FTimerHandle UniqueHandle;
		const FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &AFLevelManager::OnMapLoaded, World, MapName);
		World->GetTimerManager().SetTimer(UniqueHandle, RespawnDelegate, 2.f, false);
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void AFLevelManager::OnMapLoaded(UWorld* World, const FName MapName) { World->ServerTravel(MapName.ToString()); }

FName AFLevelManager::CleanLevelString(UObject* Context)
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	const FString Prefix = World->StreamingLevelsPrefix;
	const FString LevelName = World->GetMapName();
	return FName(*LevelName.RightChop(Prefix.Len()));
}
