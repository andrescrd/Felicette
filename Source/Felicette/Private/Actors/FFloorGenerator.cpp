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

// Called when the game starts or when spawned
void AFFloorGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void AFFloorGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!StaticMesh)
		return;

	FVector Min;
	FVector Max;

	InstancedStaticMeshComponent = NewObject<UInstancedStaticMeshComponent>(this);
	InstancedStaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	InstancedStaticMeshComponent->RegisterComponent();
	InstancedStaticMeshComponent->SetFlags(EObjectFlags::RF_Transactional);
	InstancedStaticMeshComponent->bCastDynamicShadow = false;
	InstancedStaticMeshComponent->CreationMethod = EComponentCreationMethod::SimpleConstructionScript;
	InstancedStaticMeshComponent->SetStaticMesh(StaticMesh);

	InstancedStaticMeshComponent->GetLocalBounds(Min, Max);
	const float Size = FMath::Abs(Min.X) + FMath::Abs(Max.X) + Spacing;

	const int Counter = (MaxX * MaxY );
	for (int i = 0; i < Counter; ++i)
	{
		FTransform NewTransorm;
		FVector Location = GetActorLocation();

		Location.X += i / MaxY  * Size;
		Location.Y += FMath::Fmod(i, MaxY)   * Size;
		Location.Z += 0;
		
		NewTransorm.SetLocation(Location);
		InstancedStaticMeshComponent->AddInstanceWorldSpace(NewTransorm);
	}
}
