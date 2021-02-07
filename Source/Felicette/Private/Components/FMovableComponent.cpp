// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FMovableComponent.h"
#include "Components/TimelineComponent.h"

UFMovableComponent::UFMovableComponent()
{
	OffsetZ = FFloatRange::Inclusive(-50, 50);
	TimelineTime = FFloatRange::Inclusive(.5, 3);
	bAutoActivate = true;

	MovableTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovableTimeline"));

	PrimaryComponentTick.bCanEverTick = false;
}

void UFMovableComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();

	if (bAutoActivate)
		PlayTimeline();
}

void UFMovableComponent::SetupTimeline()
{
	if (!Curve)
		return;

	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));

	FOnTimelineEvent TimelineFinished;
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinish"));

	MovableTimeline->AddInterpFloat(Curve, TimelineCallback);
	MovableTimeline->SetTimelineFinishedFunc(TimelineFinished);

	MovableTimeline->SetIgnoreTimeDilation(true);
	MovableTimeline->SetLooping(false);
}

void UFMovableComponent::PlayTimeline()
{
	GetLocationForTimeline();
	MovableTimeline->PlayFromStart();
}

void UFMovableComponent::OnTimelineHandler(float Value)
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
		CurrentActor->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value), true);
}

void UFMovableComponent::OnTimelineFinish() { PlayTimeline(); }

void UFMovableComponent::GetLocationForTimeline()
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
	{
		StartLocation = CurrentActor->GetActorLocation();
		EndLocation = StartLocation;
		EndLocation.Z += FMath::RandRange(OffsetZ.GetLowerBound().GetValue(), OffsetZ.GetUpperBound().GetValue());
		const float NewRate = 1 / FMath::RandRange(TimelineTime.GetLowerBound().GetValue(), TimelineTime.GetUpperBound().GetValue());;
		MovableTimeline->SetPlayRate(NewRate);
	}
}

void UFMovableComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	PlayTimeline();
}

void UFMovableComponent::Deactivate()
{
	Super::Deactivate();
	MovableTimeline->Deactivate();
}