// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLevelStateEnum.generated.h"

UENUM(BlueprintType)
enum class FLevelStateEnum : uint8
{
	Locked,
    Unlocked
};