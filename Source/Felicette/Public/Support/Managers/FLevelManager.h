// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Support/Structs/FLevelSetup.h"
#include "FLevelManager.generated.h"

UCLASS(Blueprintable)
class FELICETTE_API AFLevelManager : public AInfo
{
	GENERATED_BODY()

private:
	FName CleanLevelString(class UObject* Context);

protected:
	UPROPERTY(VisibleAnywhere)
	FLevelSetup CurrentLevel;
	UPROPERTY(EditDefaultsOnly)
	FLevelSetup Menu;
	UPROPERTY(EditDefaultsOnly)
	TArray<FLevelSetup> GameplayLevels;

public:
	void SetGameplayLevels(TArray<FLevelSetup> NewLevels);

	UFUNCTION(BlueprintCallable)
	void LoadLevel(class UObject* Context, FName LevelNameToLoad);
	UFUNCTION(BlueprintCallable)
	TArray<FLevelSetup> GetGameplayLevels() const;
	UFUNCTION(BlueprintCallable)
	FLevelSetup GetNextGameplayLevel(class UObject* Context);
	UFUNCTION(BlueprintCallable)
	void LoadNextGameplayLevel(class UObject* Context);
};