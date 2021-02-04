// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Support/Structs/FLevelSetup.h"

#include "FSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FELICETTE_API UFSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFSaveGame();

	UPROPERTY(VisibleAnywhere)
	TArray<FLevelSetup> Levels;	
	// UPROPERTY(VisibleAnywhere)
	// FString SaveSlotName;
	UPROPERTY(VisibleAnywhere)
	uint32 UserIndex;
};
