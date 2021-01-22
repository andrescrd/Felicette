// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/FBlueprintFunctionLibrary.h"

FColorType UFBlueprintFunctionLibrary::GetColorFromDataTable(UDataTable* Table, const FPickedTypeEnum PickedType)
{
	FColorType Color = FColorType();

	if (!Table)
		return Color;

	const int RowCount = Table->GetRowNames().Num();

	for (int i = 0; i < RowCount; ++i)
	{
		Color = *Table->FindRow<FColorType>(Table->GetRowNames()[i], "");

		if(Color.PickedType == PickedType)
			break;
	};
	
	return Color;
}
