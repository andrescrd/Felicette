#pragma once
#include "Engine/DataTable.h"
#include "Support/Enums/FPickedTypeEnum.h"
#include "FColorType.generated.h"

USTRUCT(BlueprintType)
struct FColorType : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPickedTypeEnum PickedType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ColorBase;
};
