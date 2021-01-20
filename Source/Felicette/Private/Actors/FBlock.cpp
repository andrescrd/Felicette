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

// Called when the game starts or when spawned
void AFBlock::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();
	MaterialPrimary = MeshComponent->GetMaterial(0);
}

void AFBlock::SetupTimeline()
{
	if (!IsValid(Curve))
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

		if (MaterialSecondary)
			MeshComponent->SetMaterial(0, MaterialSecondary);
	}
}

void AFBlock::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

bool AFBlock::IsValidLocation(const FVector Vector)
{
	// TODO: check if location is valid to move
	return true;
}

void AFBlock::NotifyActorBeginCursorOver()
{
	if (IsValidLocation(GetActorLocation()) && !bIsHighlighted && MaterialHeiglight)
	{
		MeshComponent->SetMaterial(0, MaterialHeiglight);
		bIsHighlighted = true;
	}
}

void AFBlock::NotifyActorEndCursorOver()
{
	if (bIsHighlighted && MaterialPrimary)
	{
		MeshComponent->SetMaterial(0, MaterialPrimary);
		bIsHighlighted = false;
	}
}
