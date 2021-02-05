// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Support/Structs/FLevelSetup.h"
#include "FLevelManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMapLoaded);

UCLASS(Blueprintable)
class FELICETTE_API AFLevelManager : public AInfo
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleInstanceOnly)
	FLevelSetup CurrentLevel;
	UPROPERTY(VisibleInstanceOnly)
	class UUserWidget* CurrentWidget;
	UPROPERTY(VisibleInstanceOnly)
	FName LastLevelLoaded;	

	UPROPERTY(EditDefaultsOnly)
	FLevelSetup Menu;
	UPROPERTY(EditDefaultsOnly)
	FLevelSetup End;	
	UPROPERTY(EditDefaultsOnly)
	TArray<FLevelSetup> GameplayLevels;	
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadingWidgetClass;
	
	UFUNCTION()
	void PreparingLevel(UWorld* World, FName Map);
	UFUNCTION(BlueprintCallable)
	void OnMapLoaded();
	
public:
	void SetGameplayLevels(TArray<FLevelSetup> NewLevels);

	UFUNCTION(BlueprintCallable)
	TArray<FLevelSetup> GetGameplayLevels() const;
	UFUNCTION(BlueprintCallable)
	FLevelSetup GetNextGameplayLevel();
	UFUNCTION(BlueprintCallable)
	void LoadNextGameplayLevel(class UWorld* World);
	UFUNCTION(BlueprintCallable)
	void LoadMenuLevel(class UWorld* Context);
	UFUNCTION(BlueprintCallable)
    void LoadEndLevel(class UWorld* Context);
	UFUNCTION(BlueprintCallable)
	void LoadGameplayLevel(class UWorld* World, FName MapName);
	UFUNCTION(BlueprintCallable)
	void Restart(class UWorld* Context);

	FOnMapLoaded FOnMapLoaded;
};
