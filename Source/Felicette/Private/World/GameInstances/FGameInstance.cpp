// Fill out your copyright notice in the Description page of Project Settings.

#include "World/GameInstances/FGameInstance.h"

#include "Support/Managers/FLevelManager.h"
#include "Support/Managers/FDataManager.h"

void UFGameInstance::Init()
{
	Super::Init();

	DataManagerInstance = NewObject<AFDataManager>(this, FName("DataManager"));
	LevelManagerInstance = NewObject<AFLevelManager>(this, LevelManagerClass, TEXT("LevelManager"));

	if (LevelManagerInstance && DataManagerInstance->GetLevels().Num() > 0)
		LevelManagerInstance->SetGameplayLevels(
			LevelManagerInstance->GetGameplayLevels().Num() > GetDataManager()->GetLevels().Num() ? LevelManagerInstance->GetGameplayLevels() : GetDataManager()->GetLevels());
}

void UFGameInstance::Shutdown() { GetDataManager()->SaveLevels(LevelManagerInstance->GetGameplayLevels()); }

void UFGameInstance::LoadGameplayFirstLevel(UObject* Context) const
{
	TArray<FLevelSetup> Levels = GetLevelManager()->GetGameplayLevels();

	if (Levels.Num() > 0)
		GetLevelManager()->LoadLevel(Context, Levels[0].LevelName);

	//TODO: print warning not level setup
}

void UFGameInstance::LoadLastLevel(UObject* Context) const
{
	const TArray<FLevelSetup> Levels = GetLevelManager()->GetGameplayLevels();

	const TArray<FLevelSetup> FilteredLevels = Levels.FilterByPredicate([](const FLevelSetup Level)
	{	
		return Level.State == FLevelStateEnum::Unlocked;
	});

	if(Levels.Num() == FilteredLevels.Num())
	{
		LoadGameplayFirstLevel(Context);
	}
	else
	{
		const int32 NextIndex = FilteredLevels.Num() -1;	
		if (Levels.IsValidIndex(NextIndex))
			GetLevelManager()->LoadLevel(Context, Levels[NextIndex].LevelName);
		else
			LoadGameplayFirstLevel(Context);
	}
}

void UFGameInstance::LoadMainMenu(UObject* Context) const { GetLevelManager()->LoadMenuLevel(Context); }

void UFGameInstance::LoadNextGameplayLevel(UObject* Context) const { GetLevelManager()->LoadNextGameplayLevel(Context); }

class AFLevelManager* UFGameInstance::GetLevelManager() const { return IsValid(LevelManagerInstance) ? LevelManagerInstance : nullptr; }

class AFDataManager* UFGameInstance::GetDataManager() const { return IsValid(DataManagerInstance) ? DataManagerInstance : nullptr; }
