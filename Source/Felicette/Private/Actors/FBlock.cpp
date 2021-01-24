// Fill out your copyright notice in the Description page of Project Settings.


#include "Felicette/Public/Actors/FBlock.h"


#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AFBlock::AFBlock()
{
	bActive = true;
	OffsetZ = -256;
	TimelineTime = 3;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(32, 32, 64));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	PrimaryActorTick.bCanEverTick = false;
}

void AFBlock::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();
	const int32 MaterilaIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
	MaterialPrimary = MeshComponent->GetMaterial(MaterilaIndex);
}

void AFBlock::SetupTimeline()
{
	if (!Curve)
		return;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));
	TimelineComponent->AddInterpFloat(Curve, TimelineCallback);

	const float NewRate = 1 / TimelineTime;
	TimelineComponent->SetPlayRate(NewRate);
	TimelineComponent->SetIgnoreTimeDilation(true);

	StartLocation = GetActorLocation();
	EndLocation = StartLocation;
	EndLocation.Z += OffsetZ;
}

void AFBlock::OnTimelineHandler(const float Output)
{
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Output));
}

void AFBlock::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (bActive && OtherActor->IsA(ACharacter::StaticClass()))
	{
		TimelineComponent->Play();
		bActive = false;

		int32 MaterilaIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
		if (MaterialSecondary)
			MeshComponent->SetMaterial(MaterilaIndex, MaterialSecondary);

		MaterilaIndex = MeshComponent->GetMaterialIndex(MaterilaSlotNameGlow);
		if (MaterialSecondary)
			MeshComponent->SetMaterial(MaterilaIndex, MaterialSecondary);
	}
}

void AFBlock::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

bool AFBlock::IsValid()
{
	// TODO: check if location is valid to move
	return true;
}

bool AFBlock::IsActive() const { return bActive; }

void AFBlock::NotifyActorBeginCursorOver()
{
	if (IsValid() && !bIsHighlighted && MaterialHeiglight && bActive)
	{
		const int32 MaterilaIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
		MeshComponent->SetMaterial(MaterilaIndex, MaterialHeiglight);
		bIsHighlighted = true;
	}
}

void AFBlock::NotifyActorEndCursorOver()
{
	if (bIsHighlighted && MaterialPrimary && bActive)
	{
		const int32 MaterilaIndex = MeshComponent->GetMaterialIndex(MaterilaSlotName);
		MeshComponent->SetMaterial(MaterilaIndex, MaterialPrimary);
		bIsHighlighted = false;
	}
}
