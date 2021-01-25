// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Support/Managers/FLevelManager.h"

#include "FGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FELICETTE_API UFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

protected:

	// Managers
	UPROPERTY(Transient)
	class AFLevelManager* LevelManagerInstance;
	UPROPERTY(Transient)
	class AFDataManager* DataManagerInstance;

	// Player Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFLevelManager> LevelManagerClass;

public:
	UFUNCTION(BlueprintCallable)
	class AFLevelManager* GetLevelManager() const;
	UFUNCTION(BlueprintCallable)
	class AFDataManager* GetDataManager() const;

	UFUNCTION(BlueprintCallable)
	void LoadGameplayFirstLevel(UObject* Context) const;
	UFUNCTION(BlueprintCallable)
	void LoadNextGameplayLevel(UObject* Context) const;
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu(UObject* Context) const;
};
