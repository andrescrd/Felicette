// Fill out your copyright notice in the Description page of Project Settings.


#include "Felicette/Public/Actors/FFloorGenerator.h"

// Sets default values
AFFloorGenerator::AFFloorGenerator()
{
	MaxX = 5;
	MaxY = 5;
	Spacing = 10;

	PrimaryActorTick.bCanEverTick = false;
}

void AFFloorGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);	
	Generate();	
}

void AFFloorGenerator::Generate()
{
	for (AActor* Child : Blocks)
	{
		if (Child != nullptr && Cast<AFBlock>(Child))
			Child->Destroy();
	}

	if (!BlockClass)
		return;

	const int BlockIndex = (MaxX * MaxY);

	FActorSpawnParameters Parameters;
	Parameters.Instigator = GetInstigator();
	Parameters.Owner = this;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < BlockIndex; ++i)
	{
		const float XOffset = (i / MaxY) * Spacing;
		const float YOffset = (FMath::Fmod(i, MaxY)) * Spacing;

		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
		AFBlock* Block = GetWorld()->SpawnActor<AFBlock>(BlockClass, BlockLocation, FRotator(0), Parameters);

		Block->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Blocks.Add(Block);
	}
}
