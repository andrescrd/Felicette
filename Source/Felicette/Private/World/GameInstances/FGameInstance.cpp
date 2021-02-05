// Fill out your copyright notice in the Description page of Project Settings.

#include "World/GameInstances/FGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Support/Managers/FLevelManager.h"
#include "Support/Managers/FDataManager.h"

void UFGameInstance::Init()
{
	Super::Init();

	DataManagerInstance = NewObject<AFDataManager>(this, FName("DataManager"));
	LevelManagerInstance = NewObject<AFLevelManager>(this, LevelManagerClass, TEXT("LevelManager"));

	if (LevelManagerInstance)
	{
		LevelManagerInstance->FOnMapLoaded.AddDynamic(this, &UFGameInstance::HandleMapLoaded);

		if (DataManagerInstance->GetLevels().Num() > 0)
		{
			const TArray<FLevelSetup> Levels = LevelManagerInstance->GetGameplayLevels().Num() > GetDataManager()->GetLevels().Num() ?
				LevelManagerInstance->GetGameplayLevels() : GetDataManager()->GetLevels();
			LevelManagerInstance->SetGameplayLevels(Levels);
		}			
	}
}

void UFGameInstance::Shutdown() { GetDataManager()->SaveLevels(LevelManagerInstance->GetGameplayLevels()); }

void UFGameInstance::LoadLastLevel(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	const TArray<FLevelSetup> Levels = GetLevelManager()->GetGameplayLevels();

	const TArray<FLevelSetup> FilteredLevels = Levels.FilterByPredicate([](const FLevelSetup Level)
	{
		return Level.State == FLevelStateEnum::Unlocked;
	});

	const int32 NextIndex = FilteredLevels.Num() - 1;
	if (Levels.IsValidIndex(NextIndex))
	{
		GetLevelManager()->LoadGameplayLevel(World, Levels[NextIndex].LevelName);
	}
}

void UFGameInstance::LoadMainMenu(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadMenuLevel(World);
}

void UFGameInstance::Restart(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->Restart(World);
}

void UFGameInstance::CleanData(UObject* Context) const
{
	GetDataManager()->ClearData();

	TArray<FLevelSetup> Levels = GetLevelManager()->GetGameplayLevels();
	for (int i = 1; i < Levels.Num(); ++i)
	{
		Levels[i].State = FLevelStateEnum::Locked;
	}

	GetLevelManager()->SetGameplayLevels(Levels);
}

void UFGameInstance::LoadNextGameplayLevel(UObject* Context) const
{
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
	GetLevelManager()->LoadNextGameplayLevel(World);
}

class AFLevelManager* UFGameInstance::GetLevelManager() const { return IsValid(LevelManagerInstance) ? LevelManagerInstance : nullptr; }

class AFDataManager* UFGameInstance::GetDataManager() const { return IsValid(DataManagerInstance) ? DataManagerInstance : nullptr; }

void UFGameInstance::HandleMapLoaded() { OnGameplayMapLoaded.Broadcast(); }
