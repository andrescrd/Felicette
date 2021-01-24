#pragma once

#include "Support/Enums/FLevelStateEnum.h"

#include "FLevelSetup.generated.h"

USTRUCT(BlueprintType)
struct FLevelSetup
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStateEnum State;

	FLevelSetup()
	{
		LevelName = TEXT("NONE");
		State = FLevelStateEnum::Locked;
	}
};