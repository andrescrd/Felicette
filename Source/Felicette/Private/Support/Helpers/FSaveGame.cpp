// Fill out your copyright notice in the Description page of Project Settings.


#include "Support/Helpers/FSaveGame.h"

UFSaveGame::UFSaveGame()
{
	SaveSlotName = TEXT("FSlot_Felix");
	UserIndex = 0;
	Levels = TArray<FLevelSetup>();
}
