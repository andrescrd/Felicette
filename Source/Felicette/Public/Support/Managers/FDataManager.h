// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Support/Structs/FLevelSetup.h"
#include "FDataManager.generated.h"

UCLASS(Blueprintable)
class FELICETTE_API AFDataManager : public AInfo
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class UFSaveGame* SaveGameInstance;
	class UFSaveGame* GetSaveGameInstance();

public:
	void SaveLevels(TArray<FLevelSetup> LevelsToSave);
	TArray<FLevelSetup> GetLevels();
	void ClearData();
};
