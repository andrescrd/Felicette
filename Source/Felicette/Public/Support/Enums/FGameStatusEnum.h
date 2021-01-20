// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGameStatusEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class FGameStatusEnum : uint8
{
	PREPARING UMETA(DisplayName ="Preparing"),
	PLAYING  UMETA(DisplayName = "Playing"),	
	COMPLETE  UMETA(DisplayName = "Complete"),		
	FINISH  UMETA(DisplayName = "Finish"),		
	UNDEFINED  UMETA(DisplayName = "Undefined"),		
};
