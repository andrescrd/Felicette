// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FMovableConstantComponent.h"
#include "Components/TimelineComponent.h"

UFMovableConstatComponent::UFMovableConstatComponent()
{
	OffsetZ = 50;
	TimelineTime = FFloatRange::Inclusive(.5, 3);
	bAutoActivate = true;

	MovableTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovableTimeline"));

	PrimaryComponentTick.bCanEverTick = false;
}

void UFMovableConstatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();

	if (bAutoActivate)
		PlayTimeline();
}

void UFMovableConstatComponent::SetupTimeline()
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

void UFMovableConstatComponent::PlayTimeline()
{
	GetLocationForTimeline();
	MovableTimeline->PlayFromStart();
}

void UFMovableConstatComponent::OnTimelineHandler(float Value)
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
		CurrentActor->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value), true);
}

void UFMovableConstatComponent::OnTimelineFinish()
{
	if (MovableTimeline->GetPlaybackPosition() <= 0.0f)
	{
		MovableTimeline->Play();
	}
	else
	{
		MovableTimeline->Reverse();
	}	
}

void UFMovableConstatComponent::GetLocationForTimeline()
{
	AActor* CurrentActor = GetOwner();

	if (CurrentActor)
	{
		StartLocation = CurrentActor->GetActorLocation();
		EndLocation = StartLocation;
		EndLocation.Z += OffsetZ;
		const float NewRate = 1 / FMath::RandRange(TimelineTime.GetLowerBound().GetValue(), TimelineTime.GetUpperBound().GetValue());;
		MovableTimeline->SetPlayRate(NewRate);
	}
}

void UFMovableConstatComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	PlayTimeline();
}

void UFMovableConstatComponent::Deactivate()
{
	Super::Deactivate();
	MovableTimeline->Deactivate();
}