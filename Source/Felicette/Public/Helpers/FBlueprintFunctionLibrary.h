// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Support/Structs/FColorType.h"

#include "FBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FELICETTE_API UFBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FColorType GetColorFromDataTable(class UDataTable *Table, FPickedTypeEnum PickedType);	
};
