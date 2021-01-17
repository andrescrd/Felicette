// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPickedTypeEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class FPickedTypeEnum : uint8
{
	DEFAULT UMETA(DisplayName ="Default"),
	RED  UMETA(DisplayName = "Red"),	
	BLUE  UMETA(DisplayName = "Blue"),	
	GREEN  UMETA(DisplayName = "Green"),	
};
