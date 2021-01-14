// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FPickup.h"

#include "Components/TimelineComponent.h"

// Sets default values
AFPickup::AFPickup()
{
	DeltaRotation = FFloatRange::Inclusive(-180, 180);
	TimelineTime = FFloatRange::Inclusive(.5, 3);
	bEnableMovement = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCanEverAffectNavigation(false);
	RootComponent = MeshComponent;

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPickup::BeginPlay()
{
	Super::BeginPlay();
	
	if(bEnableMovement)
		SetupAndPlayTimeline();
}

void AFPickup::SetupAndPlayTimeline()
{
	if (!Curve)
		return;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));

	FOnTimelineEvent TimelineFinished;
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinish"));

	TimelineComponent->AddInterpFloat(Curve, TimelineCallback);
	TimelineComponent->SetTimelineFinishedFunc(TimelineFinished);

	TimelineComponent->SetIgnoreTimeDilation(true);
	TimelineComponent->SetLooping(false);

	GetRotationForTimeline();
	TimelineComponent->Play();
}

void AFPickup::OnTimelineHandler(float Value) { SetActorRotation(FMath::Lerp(StartRotation, EndRotation, Value)); }

void AFPickup::OnTimelineFinish()
{
	GetRotationForTimeline();
	TimelineComponent->PlayFromStart();		
}

void AFPickup::GetRotationForTimeline()
{	
	StartRotation = GetActorRotation();
	EndRotation =  StartRotation;
	EndRotation.Yaw = FMath::RandRange(DeltaRotation.GetLowerBound().GetValue(), DeltaRotation.GetUpperBound().GetValue());
	const float NewRate = 1 / FMath::RandRange(TimelineTime.GetLowerBound().GetValue(), TimelineTime.GetUpperBound().GetValue());;
	TimelineComponent->SetPlayRate(NewRate);	
}